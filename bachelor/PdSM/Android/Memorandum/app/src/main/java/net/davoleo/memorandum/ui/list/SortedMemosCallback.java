package net.davoleo.memorandum.ui.list;

import android.content.Context;
import android.content.SharedPreferences;
import androidx.preference.PreferenceManager;
import androidx.recyclerview.widget.SortedList;
import com.google.common.base.Supplier;
import net.davoleo.memorandum.model.Memo;

public class SortedMemosCallback extends SortedList.Callback<Memo> {

    final Context context;

    final Supplier<MemoRecycleAdapter> linkedAdapter;

    public SortedMemosCallback(Context context, Supplier<MemoRecycleAdapter> adapter)
    {
        this.context = context;
        this.linkedAdapter = adapter;
    }

    @Override
    public int compare(Memo memo1, Memo memo2)
    {
        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(context);
        int sortingDirection = Integer.parseInt(settings.getString("sorting_direction", "-1"));
        return sortingDirection * memo1.getTimestamp().compareTo(memo2.getTimestamp());
    }

    @Override
    public void onChanged(int position, int count)
    {
        linkedAdapter.get().notifyItemRangeChanged(position, count);
    }

    @Override
    public boolean areContentsTheSame(Memo oldItem, Memo newItem)
    {
        return oldItem.title.equals(newItem.title) &&
                oldItem.description.equals(newItem.description) &&
                oldItem.status == newItem.status &&
                oldItem.getTimestamp().equals(newItem.getTimestamp()) &&
                oldItem.getLocation().equals(newItem.getLocation());
    }

    @Override
    public boolean areItemsTheSame(Memo item1, Memo item2)
    {
        return item1.uniqueId == item2.uniqueId;
    }

    @Override
    public void onInserted(int position, int count)
    {
        linkedAdapter.get().notifyItemRangeInserted(position, count);
    }

    @Override
    public void onRemoved(int position, int count)
    {
        linkedAdapter.get().notifyItemRangeRemoved(position, count);
    }

    @Override
    public void onMoved(int fromPosition, int toPosition)
    {

    }
}
