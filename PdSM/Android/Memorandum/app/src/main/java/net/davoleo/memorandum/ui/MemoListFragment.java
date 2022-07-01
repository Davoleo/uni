package net.davoleo.memorandum.ui;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
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

/**
 * A fragment representing a list of Items.
 */
public class MemoListFragment extends Fragment {

    private static final String TAG = "MemoListFragment";
    public static ExecutorService memoListExecutor = Executors.newFixedThreadPool(4);

    /**
     * Mandatory empty constructor for the fragment manager to instantiate the
     * fragment (e.g. upon screen orientation changes).
     */
    public MemoListFragment()
    {
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        return inflater.inflate(R.layout.fragment_memo_list, container, false);
    }

    @SuppressLint("NotifyDataSetChanged")
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState)
    {
        // Set the adapter
        if (view instanceof RecyclerView && this.getActivity() instanceof MainActivity)
        {
            Context context = view.getContext();
            RecyclerView recyclerView = (RecyclerView) view;
            recyclerView.setLayoutManager(new LinearLayoutManager(context));
            DividerItemDecoration dividers = new DividerItemDecoration(recyclerView.getContext(), ((LinearLayoutManager) recyclerView.getLayoutManager()).getOrientation());
            recyclerView.addItemDecoration(dividers);
            MemoRecycleAdapter adapter = new MemoRecycleAdapter(this.getContext(), new ArrayList<>());
            recyclerView.setAdapter(adapter);

            ProgressBar progressIndicator = this.getActivity().findViewById(R.id.progress_circular);
            progressIndicator.setVisibility(View.VISIBLE);

            //Get Data for population
            Future<List<Memo>> futureMemos = memoListExecutor.submit(() -> MemorandumDatabase.instance.memoDAO().getAll());
            memoListExecutor.submit(() -> {
                try
                {
                    List<Memo> memoList = futureMemos.get();

                    for (Memo memo : memoList)
                        memo.getLocation().reverseGeocode();

                    Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                        ((MainActivity) getActivity()).memos = memoList;
                        progressIndicator.setVisibility(View.GONE);
                        adapter.setData(memoList);
                        adapter.notifyDataSetChanged();
                    });

                } catch (ExecutionException | InterruptedException e) {
                    Log.w(TAG, "onCreateView: Data Population failed due to " + e.getLocalizedMessage());
                }
            });

            //FAB Hiding when scrolling
            FloatingActionButton fab = this.getActivity().findViewById(R.id.fab);
            recyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
                @Override
                public void onScrollStateChanged(@NonNull RecyclerView recyclerView, int newState)
                {
                    if (newState == RecyclerView.SCROLL_STATE_IDLE)
                        fab.show();
                    super.onScrollStateChanged(recyclerView, newState);
                }

                @Override
                public void onScrolled(@NonNull RecyclerView recyclerView, int dx, int dy)
                {
                    if (dy > 0 || dy < 0 && fab.isShown())
                        fab.hide();
                }
            });
        }
    }
}