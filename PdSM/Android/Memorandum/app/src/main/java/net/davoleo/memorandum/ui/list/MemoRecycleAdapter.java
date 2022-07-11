package net.davoleo.memorandum.ui.list;

import android.content.Context;
import android.location.Address;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.SortedList;
import com.google.android.material.chip.Chip;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.databinding.FragmentMemoItemBinding;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.ui.MainActivity;
import net.davoleo.memorandum.ui.MemoListFragment;
import net.davoleo.memorandum.util.Utils;

import java.text.DateFormat;
import java.util.Locale;

public class MemoRecycleAdapter extends RecyclerView.Adapter<MemoRecycleAdapter.ViewHolder> {

    private final Context context;
    protected SortedList<Memo> memos;

    public MemoRecycleAdapter(MemoListFragment fragment, SortedList<Memo> items)
    {
        this.context = fragment.getContext();
        memos = items;
    }

    public void setData(SortedList<Memo> values)
    {
        this.memos = values;
    }

    protected void onSwiped(int position, MemoStatus newStatus) {
        Memo memo = memos.get(position);
        memo.status = newStatus;
        notifyItemChanged(position);

        MainActivity.memorandumExecutor.submit(
                () -> MemorandumDatabase.instance.memoDAO().updateMemo(memos.get(position))
        );
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
        Memo memo = memos.get(position);

        holder.memoTitle.setText(memo.title);
        holder.memoDescription.setText(memo.description);

        holder.memoStatus.setText(memo.status.toString());
        holder.memoStatus.setChipIconResource(memo.status.getIcon());
        holder.memoStatus.setChipIconSize(Utils.convertDpToPx(context, 16));

        ////Re-inflate chip into the filter layout
        //holder.memoStatus.setOnClickListener(v -> {
        //    if (filterLayout.getVisibility() == View.VISIBLE)
        //        return;
        //
        //    Chip original = (Chip) v;
        //
        //    View layout = LayoutInflater.from(context).inflate(R.layout.chip, filterLayout);
        //    Chip newChip = layout.findViewById(R.id.filter_chip);
        //
        //    newChip.setText(original.getText());
        //    newChip.setChipIconResource(android.R.drawable.ic_menu_close_clear_cancel);
        //    newChip.setChipStrokeColor(original.getChipStrokeColor());
        //    newChip.setChipBackgroundColor(original.getChipBackgroundColor());
        //    newChip.setOnClickListener(chipView -> {
        //        filterLayout.removeViewAt(1);
        //        filterLayout.setVisibility(View.GONE);
        //    });
        //
        //    filterLayout.setVisibility(View.VISIBLE);
        //});

        switch (memo.status) {
            case COMPLETE:
                holder.memoStatus.setChipBackgroundColorResource(R.color.green_400);
                holder.memoStatus.setChipStrokeColorResource(R.color.green_dark);
                break;
            case ACTIVE:
                holder.memoStatus.setChipBackgroundColorResource(R.color.lime_500);
                holder.memoStatus.setChipStrokeColorResource(R.color.lime_dark);
                break;
            case EXPIRED:
                holder.memoStatus.setChipBackgroundColorResource(R.color.memostatus_red);
                holder.memoStatus.setChipStrokeColorResource(R.color.memostatus_darkred);
                break;
        }

        //int currentDay = calendar.get(Calendar.DAY_OF_YEAR);
        //calendar.setTime(memo.getTimestamp());
        //int memoDay = calendar.get(Calendar.DAY_OF_YEAR);
        // TODO: 30/06/2022 Use different formats depending on the current date
        DateFormat dateformat = android.text.format.DateFormat.getDateFormat(context);
        holder.memoTimestamp.setText(dateformat.format(memo.getTimestamp()).replaceFirst(" ", "\n"));

        Address address = memo.getLocation().getAddress();
        String locationString = "";

        if (address != null) {
            locationString = Utils.joinStrings(" ",
                    (address.getThoroughfare() != null ? address.getThoroughfare() : ""),
                    (address.getSubThoroughfare() != null ? address.getSubThoroughfare() : ""),
                    (address.getLocality() != null ? address.getLocality() : "")
            );
        }

        if (locationString.isEmpty()) {
            locationString = String.format(
                    Locale.getDefault(),
                    "Lat: %f\nLon: %f",
                    memo.getLocation().getLatitude(),
                    memo.getLocation().getLongitude()
            );
        }

        holder.memoLocation.setText(locationString);
    }

    @Override
    public int getItemCount()
    {
        return memos.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {

        private final TextView memoTitle;
        private final TextView memoDescription;
        private final Chip memoStatus;
        private final TextView memoTimestamp;
        private final TextView memoLocation;

        public ViewHolder(FragmentMemoItemBinding binding)
        {
            super(binding.getRoot());
            this.memoTitle = binding.memoTitle;
            this.memoDescription = binding.memoDescription;
            this.memoStatus = binding.memoStatus;
            this.memoTimestamp = binding.memoTimestamp;
            this.memoLocation = binding.memoLocation;
        }

        public Chip getStatusChip()
        {
            return memoStatus;
        }
    }
}