package net.davoleo.memorandum.ui.main;

import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import net.davoleo.memorandum.databinding.FragmentMemoItemBinding;
import net.davoleo.memorandum.model.Memo;

import java.util.List;

public class MemoRecycleAdapter extends RecyclerView.Adapter<MemoRecycleAdapter.ViewHolder> {

    private final List<Memo> values;

    public MemoRecycleAdapter(List<Memo> items)
    {
        values = items;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        FragmentMemoItemBinding binding =
                FragmentMemoItemBinding.inflate(LayoutInflater.from(parent.getContext()), parent, false);
        return new ViewHolder(binding);
    }

    @Override
    public void onBindViewHolder(final ViewHolder holder, int position)
    {
        Memo memo = values.get(position);

        holder.memoTitle.setText(memo.title);
        holder.memoDescription.setText(memo.description);
        holder.memoStatus.setText(memo.status.toString());
    }

    @Override
    public int getItemCount()
    {
        return values.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {

        private final TextView memoTitle;
        private final TextView memoDescription;
        private final TextView memoStatus;

        public ViewHolder(FragmentMemoItemBinding binding)
        {
            super(binding.getRoot());
            this.memoTitle = binding.memoTitle;
            this.memoDescription = binding.memoDescription;
            this.memoStatus = binding.memoStatus;
        }
    }
}