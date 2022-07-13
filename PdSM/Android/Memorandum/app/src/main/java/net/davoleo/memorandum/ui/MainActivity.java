package net.davoleo.memorandum.ui;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
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

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity implements TabLayout.OnTabSelectedListener {

    private static final String TAG = "MainActivity";


    //UI
    private TabLayout tabs;
    protected ProgressBar progressIndicator;

    //FRAGMENTS
    private MemoListFragment listFragment;
    private Fragment mapFragment;

    //CONCURRENCY
    public static ExecutorService memorandumExecutor = Executors.newFixedThreadPool(4);

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        //Initialize DB
        MemorandumDatabase.init(this);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        progressIndicator = findViewById(R.id.progress_circular);
        progressIndicator.setVisibility(View.VISIBLE);

        tabs = findViewById(R.id.tabs);
        tabs.addOnTabSelectedListener(this);

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
                MainActivity.memorandumExecutor.submit(() -> {
                    MemorandumDatabase.instance.memoDAO().insertOne(memo);

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
        SharedPreferences.Editor editablePrefs = Utils.getSharedPreferences(this).edit();
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Pick a Status to filter Memos (Dismiss to unset the filter)");
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
        builder.setOnCancelListener(dialog -> {
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
}