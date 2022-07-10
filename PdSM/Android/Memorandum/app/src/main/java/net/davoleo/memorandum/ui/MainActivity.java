package net.davoleo.memorandum.ui;

import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Geocoder;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ProgressBar;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.tabs.TabLayout;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.util.Utils;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class MainActivity extends AppCompatActivity implements TabLayout.OnTabSelectedListener {

    private static final String TAG = "MainActivity";


    //UI
    private TabLayout tabs;
    protected ProgressBar progressIndicator;

    //FRAGMENTS
    private MemoListFragment listFragment;
    private Fragment mapFragment;

    //DATA
    protected List<Memo> memos = new ArrayList<>();
    @Nullable
    protected MemoStatus filteredStatus = MemoStatus.ACTIVE;

    //PREFERENCES
    private SharedPreferences preferences;

    //CONCURRENCY
    public static ExecutorService memorandumExecutor = Executors.newFixedThreadPool(4);

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        //Init shared preferences
        preferences = getSharedPreferences(getString(R.string.memorandum_shared_prefs), MODE_PRIVATE);
        //Load filtering settings
        // TODO: 09/07/2022 Debug why this is not working correctly 
        preferences.getInt("memo_filter", MemoStatus.ACTIVE.ordinal());

        //Initialize DB
        MemorandumDatabase.init(this);
        //Initialize Geocoder
        Utils.geocoder = new Geocoder(this);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        progressIndicator = findViewById(R.id.progress_circular);
        progressIndicator.setVisibility(View.VISIBLE);

        tabs = findViewById(R.id.tabs);
        tabs.addOnTabSelectedListener(this);

        //Get Data for population
        Future<List<Memo>> futureMemos = MainActivity.memorandumExecutor.submit(() -> MemorandumDatabase.instance.memoDAO().getAll());
        MainActivity.memorandumExecutor.submit(() -> {
            try
            {
                List<Memo> memoList = futureMemos.get();

                for (Memo memo : memoList)
                    memo.getLocation().reverseGeocode();

                Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                    memos.clear();
                    memos.addAll(memoList);
                    onTabSelected(tabs.getTabAt(0));
                    progressIndicator.setVisibility(View.GONE);
                });

            } catch (ExecutionException | InterruptedException e) {
                Log.w(TAG, "onCreate: Data Population failed due to " + e.getLocalizedMessage());
            }
        });


        listFragment = new MemoListFragment();
        mapFragment = new Fragment(); //TODO Placeholder

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(view ->
                startActivityForResult(new Intent(getApplicationContext(), MemoAddActivity.class), 1)
        );
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        if (listFragment.isVisible()) {
            listFragment.processMemoList(memos, filteredStatus);
        }
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
                this.memos.add(memo);
                memorandumExecutor.submit(() -> {
                    MemorandumDatabase.instance.memoDAO().insertOne(memo);

                    Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                        if (listFragment.isVisible()) {
                            listFragment.addMemoToProcessedList(memo, filteredStatus);
                        }
                    });
                });
            }
        }
    }

    @Override
    public void onTabSelected(TabLayout.Tab tab)
    {
        if (tabs.getSelectedTabPosition() == 0) {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.replace(R.id.main_container_layout, this.listFragment);
            transaction.setCustomAnimations(R.anim.slide_right_in, R.anim.slide_right_out);
            transaction.commit();
        }
        else if (tabs.getSelectedTabPosition() == 1) {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.replace(R.id.main_container_layout, this.mapFragment);
            transaction.setCustomAnimations(R.anim.slide_left_in, R.anim.slide_left_out);
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
        SharedPreferences.Editor editablePrefs = preferences.edit();
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Pick a Status to filter Memos (Dismiss to unset the filter)");
        builder.setSingleChoiceItems(
                MemoStatus.NAMES,
                filteredStatus == null ? -1 : filteredStatus.ordinal(),
                (dialog, which) -> {
                    if (filteredStatus == null || which != filteredStatus.ordinal())
                    {
                        editablePrefs.putInt("memo_filter", which);
                        editablePrefs.apply();
                        filteredStatus = MemoStatus.byIndex(which);
                        listFragment.processMemoList(memos, filteredStatus);
                        listFragment.recyclerView.getAdapter().notifyDataSetChanged();
                    }
                    dialog.dismiss();
                }
        );
        builder.setOnCancelListener(dialog -> {
            if (filteredStatus != null)
            {
                editablePrefs.putInt("memo_filter", -1);
                editablePrefs.apply();
                filteredStatus = null;
                listFragment.processMemoList(memos, null);
                listFragment.recyclerView.getAdapter().notifyDataSetChanged();
            }
        });

        AlertDialog filterDialog = builder.create();
        filterDialog.show();
    }

    public void openSettings(MenuItem item) {
        Intent intent = new Intent(getApplicationContext(), SettingsActivity.class);
        startActivity(intent);
    }
}