package net.davoleo.memorandum.ui.list;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.util.Pair;
import android.view.View;
import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.RecyclerView;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.util.Utils;

public class ItemSwipeCallback extends ItemTouchHelper.SimpleCallback {

    private static final int DIR_FLAGS = ItemTouchHelper.START | ItemTouchHelper.END;

    private final Context context;

    private final MemoRecycleAdapter adapter;


    //Graphics Items:
    private ColorDrawable background = new ColorDrawable();
    private Paint clearPaint = new Paint() {{
        setXfermode(new PorterDuffXfermode(PorterDuff.Mode.CLEAR));
    }};

    @SuppressWarnings("unchecked")
    private final Pair<MemoStatus, MemoStatus>[] complementaryStatuses = new Pair[]{
        Pair.create(MemoStatus.EXPIRED, MemoStatus.COMPLETE),
                Pair.create(MemoStatus.ACTIVE, MemoStatus.COMPLETE),
                Pair.create(MemoStatus.ACTIVE, MemoStatus.EXPIRED)
    };


    public ItemSwipeCallback(Context context, MemoRecycleAdapter adapter)
    {
        super(DIR_FLAGS, DIR_FLAGS);
        this.adapter = adapter;
        this.context = context;
    }

    @Override
    public boolean onMove(@NonNull RecyclerView recyclerView, @NonNull RecyclerView.ViewHolder viewHolder, @NonNull RecyclerView.ViewHolder target)
    {
        return false;
    }

    @Override
    public void onSwiped(@NonNull RecyclerView.ViewHolder viewHolder, int direction)
    {
        if (!(viewHolder instanceof MemoRecycleAdapter.ViewHolder))
            return;

        int statusIdx = Utils.indexOf(MemoStatus.NAMES, ((MemoRecycleAdapter.ViewHolder) viewHolder).getStatusChip().getText());

        if (direction == ItemTouchHelper.START)
            adapter.onSwiped(viewHolder.getBindingAdapterPosition(), complementaryStatuses[statusIdx].second);
        else if (direction == ItemTouchHelper.END)
            adapter.onSwiped(viewHolder.getBindingAdapterPosition(), complementaryStatuses[statusIdx].first);

        adapter.notifyItemChanged(viewHolder.getBindingAdapterPosition());
    }

    @Override
    public void onChildDraw(@NonNull Canvas c, @NonNull RecyclerView recyclerView, @NonNull RecyclerView.ViewHolder viewHolder, float dX, float dY, int actionState, boolean isCurrentlyActive)
    {

        if (actionState != ItemTouchHelper.ACTION_STATE_SWIPE) {
            super.onChildDraw(c, recyclerView, viewHolder, dX, dY, actionState, isCurrentlyActive);
            return;
        }

        if (!(viewHolder instanceof MemoRecycleAdapter.ViewHolder)) {
            return;
        }

        String chipText =  ((MemoRecycleAdapter.ViewHolder) viewHolder).getStatusChip().getText().toString();
        Pair<MemoStatus, MemoStatus> compl = complementaryStatuses[Utils.indexOf(MemoStatus.NAMES, chipText)];

        View itemView = viewHolder.itemView;
        int itemHeight = itemView.getBottom() - itemView.getTop();

        //Cancelled swipe
        if (dX == 0F && !isCurrentlyActive) {
            clearCanvas(c, itemView.getRight() + dX, itemView.getTop(), itemView.getRight(), itemView.getBottom());
            super.onChildDraw(c, recyclerView, viewHolder, dX, dY, actionState, isCurrentlyActive);
            return;
        }

        if (dX > 0) {

            //Draw Background
            background.setColor(compl.first.getColor());
            background.setBounds(itemView.getLeft(), itemView.getTop(), (int) (itemView.getLeft() + dX), itemView.getBottom());
            background.draw(c);

            Drawable icon = ContextCompat.getDrawable(context, compl.first.getIcon());
            assert icon != null;

            int iconTop = itemView.getTop() + (itemHeight - icon.getIntrinsicHeight()) / 2;
            int iconMargin = (itemHeight - icon.getIntrinsicHeight()) / 2;
            int iconLeft = itemView.getLeft() + iconMargin;
            int iconRight = itemView.getLeft() + iconMargin + icon.getIntrinsicWidth();
            int iconBottom = iconTop + icon.getIntrinsicHeight();

            final float alpha = Math.abs(dX) / viewHolder.itemView.getWidth();
            icon.setAlpha((int) (alpha * 255));

            icon.setBounds(iconLeft, iconTop, iconRight, iconBottom);
            icon.draw(c);
        }
        else {

            //Draw Background
            background.setColor(compl.second.getColor());
            background.setBounds((int) (itemView.getRight() + dX), itemView.getTop(), itemView.getRight(), itemView.getBottom());
            background.draw(c);

            Drawable icon = ContextCompat.getDrawable(context, compl.second.getIcon());
            assert icon != null;

            int iconTop = itemView.getTop() + (itemHeight - icon.getIntrinsicHeight()) / 2;
            int iconMargin = (itemHeight - icon.getIntrinsicHeight()) / 2;
            int iconLeft = itemView.getRight() - iconMargin - icon.getIntrinsicWidth();
            int iconRight = itemView.getRight() - iconMargin;
            int iconBottom = iconTop + icon.getIntrinsicHeight();

            final float alpha = Math.abs(dX) / viewHolder.itemView.getWidth();
            icon.setAlpha((int) (alpha * 255));

            icon.setBounds(iconLeft, iconTop, iconRight, iconBottom);
            icon.draw(c);

            //icon.setTranslationX(dX);
        }

        super.onChildDraw(c, recyclerView, viewHolder, dX, dY, actionState, isCurrentlyActive);

    }

    private void clearCanvas(Canvas canvas, float left, float top, float right, float bottom) {
        canvas.drawRect(left, top, right, bottom, clearPaint);
    }
}
