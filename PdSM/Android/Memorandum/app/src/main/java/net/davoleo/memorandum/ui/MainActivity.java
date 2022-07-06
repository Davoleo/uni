package net.davoleo.memorandum.ui;

import android.content.Intent;
import android.location.Geocoder;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.ProgressBar;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.tabs.TabLayout;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
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


    private TabLayout tabs;
    protected ProgressBar progressIndicator;

    protected List<Memo> memos = new ArrayList<>();

    private MemoListFragment listFragment;
    private Fragment mapFragment;

    public static ExecutorService memorandumExecutor = Executors.newFixedThreadPool(4);

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        //Initialize DB
        MemorandumDatabase.init(this);
        //Initialize Geocoder
        Utils.geocoder = new Geocoder(this);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        progressIndicator = findViewById(R.id.progress_circular);
        progressIndicator.setVisibility(View.VISIBLE);

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
                    progressIndicator.setVisibility(View.GONE);
                });

            } catch (ExecutionException | InterruptedException e) {
                Log.w(TAG, "onCreate: Data Population failed due to " + e.getLocalizedMessage());
            }
        });


        listFragment = (MemoListFragment) getSupportFragmentManager().findFragmentById(R.id.main_container_layout);
        mapFragment = new Fragment(); //TODO Placeholder

        tabs = findViewById(R.id.tabs);
        tabs.addOnTabSelectedListener(this);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(view ->
                startActivityForResult(new Intent(getApplicationContext(), MemoAddActivity.class), 1)
        );
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
                int newMemoIndex = memos.size();
                this.memos.add(memo);
                memorandumExecutor.submit(() -> {
                    MemorandumDatabase.instance.memoDAO().insertOne(memo);

                    Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                        if (listFragment.isVisible()) {
                            listFragment.recyclerView.getAdapter().notifyItemInserted(newMemoIndex);
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
}