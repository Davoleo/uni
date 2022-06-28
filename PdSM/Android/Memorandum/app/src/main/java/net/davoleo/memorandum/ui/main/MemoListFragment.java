package net.davoleo.memorandum.ui.main;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import com.google.common.collect.Lists;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.ui.MainActivity;

import java.util.List;
import java.util.concurrent.*;

/**
 * A fragment representing a list of Items.
 */
public class MemoListFragment extends Fragment {

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
        View view = inflater.inflate(R.layout.fragment_memo_list, container, false);

        // Set the adapter
        if (view instanceof RecyclerView && this.getActivity() instanceof MainActivity)
        {
            // TODO: 27/06/2022 ASYNC CALL TO RETRIEVE DATA
            //Thread thread = new Thread(() -> {
            //    List<Memo> memos = MemorandumDatabase.instance.memoDAO().getAll();
            //    new Handler(Looper.getMainLooper()).post(() -> {
            //
            //    });
            //});

            List<Memo> memos = Lists.newArrayList(
                    new Memo("Test0", "aaaaaaaaaaa", MemoStatus.COMPLETE),
                    new Memo("Test1", "bbbbbbbbbbbbbbbbbbb", MemoStatus.ACTIVE),
                    new Memo("Test2", "ccc", MemoStatus.COMPLETE),
                    new Memo("Test3", "MATPAC", MemoStatus.EXPIRED)
                    );

            Context context = view.getContext();
            RecyclerView recyclerView = (RecyclerView) view;
            recyclerView.setLayoutManager(new LinearLayoutManager(context));
            recyclerView.setAdapter(new MemoRecycleAdapter(memos));
        }
        return view;
    }
}