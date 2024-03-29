package net.davoleo.memorandum.ui;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ProgressBar;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.coordinatorlayout.widget.CoordinatorLayout;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;
import com.google.android.gms.location.Geofence;
import com.google.android.gms.location.GeofencingRequest;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.tabs.TabLayout;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.util.GeofencingUtils;
import net.davoleo.memorandum.util.Utils;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity implements TabLayout.OnTabSelectedListener {

    private static final String TAG = "MainActivity";
    public static final int REQUEST_PERMISSIONS_CODE = 34;

    //Geofencing
    protected GeofencingUtils geofencingHelper;

    //UI
    private CoordinatorLayout coordinatorLayout;
    private TabLayout tabs;
    protected ProgressBar progressIndicator;

    //FRAGMENTS
    private MemoListFragment listFragment;
    private Fragment mapFragment;

    //CONCURRENCY
    public static ExecutorService memorandumExecutor = Executors.newFixedThreadPool(4);

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        //Initialize DB
        MemorandumDatabase.init(this);

        geofencingHelper = new GeofencingUtils(this);

        if (Utils.hasLocationPermissions(this)) {
            Utils.requestLocationPermissions(this, coordinatorLayout);
        }

        if (Utils.hasLocationPermissions(this)) {

            memorandumExecutor.submit(() -> {
                List<Memo> memos = MemorandumDatabase.instance.memoDAO().getAllOfStatus(MemoStatus.ACTIVE);

                for (Memo memo : memos)
                {
                    Geofence fence = geofencingHelper.createGeofence(memo.getLocation());
                    GeofencingRequest request = geofencingHelper.createGeofencingRequest(fence);
                    geofencingHelper.client
                            .addGeofences(request, geofencingHelper.getPendingIntent(memo))
                            .addOnFailureListener(GeofencingUtils::debugLogGeofencingTask)
                            .addOnSuccessListener(GeofencingUtils::debugLogGeofencingTask);
                }

            });
        }

        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        progressIndicator = findViewById(R.id.progress_circular);
        progressIndicator.setVisibility(View.VISIBLE);

        coordinatorLayout = findViewById(R.id.main_coordinator_layout);

        tabs = findViewById(R.id.tabs);
        tabs.addOnTabSelectedListener(this);

        listFragment = (MemoListFragment) getSupportFragmentManager().findFragmentByTag("FRAGMENT_LIST");
        mapFragment = new MemoMapFragment();

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(view ->
                startActivityForResult(new Intent(getApplicationContext(), MemoAddActivity.class), 1)
        );
    }

    @Override
    protected void onStart()
    {
        super.onStart();

        if (!Utils.hasLocationPermissions(this)) {
            Utils.requestLocationPermissions(this, coordinatorLayout);
        }
        //Now that permissions have been granted app can do stuff
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        if (data != null) {
            //AddMemo Activity Result
            if (requestCode == 1 && resultCode == RESULT_OK) {
                Memo memo = Memo.fromBundle(data.getExtras());
                listFragment.addMemoToProcessedList(memo);
            }
        }
    }

    @Override
    public void onTabSelected(TabLayout.Tab tab)
    {

        if (tabs.getSelectedTabPosition() == 0) {
            //Protect against list fragment becoming null due to inflating issues
            if (listFragment == null) {
                Snackbar.make(coordinatorLayout, "Memo List Tab is currently unavailable", Snackbar.LENGTH_SHORT).show();
                return;
            }

            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.setCustomAnimations(R.anim.slide_right_in, R.anim.slide_right_out);
            transaction.replace(R.id.main_container_layout, this.listFragment);
            transaction.commit();
        }
        else if (tabs.getSelectedTabPosition() == 1) {
            //Protect against list fragment becoming null due to inflating issues
            if (mapFragment == null) {
                Snackbar.make(coordinatorLayout, "Memo Map Tab is currently unavailable", Snackbar.LENGTH_SHORT).show();
                return;
            }


            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.setCustomAnimations(R.anim.slide_left_in, R.anim.slide_left_out);
            transaction.replace(R.id.main_container_layout, this.mapFragment);
            transaction.commit();
        }
    }

    @Override
    public void onTabUnselected(TabLayout.Tab tab)
    {}

    @Override
    public void onTabReselected(TabLayout.Tab tab)
    {}

    public void filterMemos(MenuItem menuButton) {
        SharedPreferences.Editor editablePrefs = Utils.getSharedPreferences(this).edit();
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Pick a Status to filter Memos");
        builder.setSingleChoiceItems(
                MemoStatus.NAMES,
                listFragment.filteredStatus == null ? -1 : listFragment.filteredStatus.ordinal(),
                (dialog, which) -> {
                    if (listFragment.filteredStatus == null || which != listFragment.filteredStatus.ordinal())
                    {
                        editablePrefs.putInt("memo_filter", which);
                        editablePrefs.apply();
                        listFragment.filteredStatus = MemoStatus.byIndex(which);
                        listFragment.queryMemoList();
                    }
                    dialog.dismiss();
                }
        );
        builder.setNegativeButton("Unset", (dialog, which) -> {
            if (listFragment.filteredStatus != null)
            {
                editablePrefs.putInt("memo_filter", -1);
                editablePrefs.apply();
                listFragment.filteredStatus = null;
                listFragment.queryMemoList();
            }
        });

        AlertDialog filterDialog = builder.create();
        filterDialog.show();
    }

    public void openSettings(MenuItem item) {
        Intent intent = new Intent(getApplicationContext(), SettingsActivity.class);
        startActivity(intent);
    }

    /// Permissions
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
    {
        if (requestCode == REQUEST_PERMISSIONS_CODE) {
            if (grantResults.length <= 0) {
                Log.d(TAG, "onRequestPermissionsResult: User Interaction Cancelled");
            }
            else if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Log.d(TAG, "onRequestPermissionsResult: Location Permission Granted");
            }
            else {
                Snackbar.make(coordinatorLayout, "Location Permissions have been denied, you can change this from the settings", Snackbar.LENGTH_SHORT);
            }
        }
    }
}