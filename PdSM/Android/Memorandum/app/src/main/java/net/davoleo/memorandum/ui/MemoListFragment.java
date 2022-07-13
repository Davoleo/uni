package net.davoleo.memorandum.ui;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.*;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.*;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.ui.list.ItemSwipeCallback;
import net.davoleo.memorandum.ui.list.MemoRecycleAdapter;
import net.davoleo.memorandum.ui.list.SortedMemosCallback;
import net.davoleo.memorandum.util.Utils;

import java.util.List;

/**
 * A fragment representing a list of Items.
 */
public class MemoListFragment extends Fragment implements MemoRecycleAdapter.OnItemLongClickListener {

    private static final String TAG = "MemoListFragment";
    protected RecyclerView recyclerView;

    protected SortedList<Memo> processedList;

    @Nullable
    protected MemoStatus filteredStatus = MemoStatus.ACTIVE;

    private int longPressedElementIndex = -1;


    /**
     * Mandatory empty constructor for the fragment manager to instantiate the
     * fragment (e.g. upon screen orientation changes).
     */
    public MemoListFragment()
    {

    }

    @SuppressLint("NotifyDataSetChanged")
    protected void queryMemoList() {
        MainActivity.memorandumExecutor.submit(() -> {

            List<Memo> memos;
            if (filteredStatus != null)
                memos = MemorandumDatabase.instance.memoDAO().getAllOfStatus(filteredStatus);
            else
                memos = MemorandumDatabase.instance.memoDAO().getAll();

            for (Memo memo : memos)
                memo.getLocation().reverseGeocode(getContext());

            Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                this.processedList.replaceAll(memos);

                if (getActivity() instanceof MainActivity)
                    ((MainActivity) getActivity()).progressIndicator.setVisibility(View.GONE);

                if (recyclerView != null && recyclerView.getAdapter() != null)
                    recyclerView.getAdapter().notifyDataSetChanged();
            });
        });

        Log.d(TAG, "queryMemoList: Querying Memos from Database");
    }

    private void removeMemoFromProcessedList(final Memo memo) {
        processedList.remove(memo);

        MainActivity.memorandumExecutor.submit(() -> MemorandumDatabase.instance.memoDAO().delete(memo));
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState)
    {
        return inflater.inflate(R.layout.fragment_memo_list, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState)
    {
        if (!(view instanceof RecyclerView))
            return;


        recyclerView = (RecyclerView) view;
        //Set Recycler View Linear Layout Manager
        recyclerView.setLayoutManager(new LinearLayoutManager(view.getContext()));
        //Add Divider Decoration
        DividerItemDecoration dividers = new DividerItemDecoration(recyclerView.getContext(), ((LinearLayoutManager) recyclerView.getLayoutManager()).getOrientation());
        recyclerView.addItemDecoration(dividers);

        //Load filtering settings
        filteredStatus = MemoStatus.byIndex(Utils.getSharedPreferences(getContext()).getInt("memo_filter", MemoStatus.ACTIVE.ordinal()));
        processedList = new SortedList<>(Memo.class, new SortedMemosCallback(this.getContext(), () -> (MemoRecycleAdapter) recyclerView.getAdapter()));

        //Set Memo Recycler Adapter
        MemoRecycleAdapter adapter = new MemoRecycleAdapter(this, processedList);
        adapter.setLongClickListener(this);
        recyclerView.setAdapter(adapter);
        registerForContextMenu(recyclerView);

        queryMemoList();

        ItemTouchHelper touchHelper = new ItemTouchHelper(new ItemSwipeCallback(getContext(), adapter));
        touchHelper.attachToRecyclerView(recyclerView);

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

    @Override
    public void onItemLongClicked(View view, int position)
    {
        longPressedElementIndex = position;
        view.showContextMenu();
    }

    @Override
    public void onCreateContextMenu(@NonNull ContextMenu menu, @NonNull View v, @Nullable ContextMenu.ContextMenuInfo menuInfo)
    {
        super.onCreateContextMenu(menu, v, menuInfo);
        MenuInflater inflater = getActivity().getMenuInflater();
        inflater.inflate(R.menu.menu_memo_contextual, menu);
    }

    @Override
    public boolean onContextItemSelected(@NonNull MenuItem item)
    {
        int actionId = item.getItemId();

        if (actionId == R.id.context_remove_memo && longPressedElementIndex > -1 && longPressedElementIndex < processedList.size()) {
            removeMemoFromProcessedList(processedList.get(longPressedElementIndex));
        }

        return true;
    }
}