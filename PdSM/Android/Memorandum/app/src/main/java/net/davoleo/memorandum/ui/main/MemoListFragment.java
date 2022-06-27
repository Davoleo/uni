package net.davoleo.memorandum.ui.main;

import android.content.Context;
import android.os.Bundle;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.ui.MainActivity;

import java.util.List;

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
            MemorandumDatabase.instance.memoDAO().getAllLive().observe(this, memos -> {

            });

            Context context = view.getContext();
            RecyclerView recyclerView = (RecyclerView) view;
            recyclerView.setLayoutManager(new LinearLayoutManager(context));
            recyclerView.setAdapter(new MemoRecycleAdapter(memos));
        }
        return view;
    }
}