package net.davoleo.memorandum.ui.dialog;

import android.content.Context;
import android.text.format.DateFormat;
import android.widget.TextView;
import com.google.android.material.bottomsheet.BottomSheetDialog;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.persistence.TypeConverters;

public class MemoDetailsDialog {

    public static void show(Context context, Memo memo) {
        final BottomSheetDialog bottomSheetDialog = new BottomSheetDialog(context);
        bottomSheetDialog.setContentView(R.layout.show_details_dialog);

        TextView titleView = bottomSheetDialog.findViewById(R.id.titleView);
        assert titleView != null;
        titleView.setText(memo.title);

        TextView descView  = bottomSheetDialog.findViewById(R.id.descView);
        assert descView != null;
        descView.setText(memo.description);

        TextView timestampView = bottomSheetDialog.findViewById(R.id.timestampView);
        assert timestampView != null;
        timestampView.setText(DateFormat.getDateFormat(context).format(memo.getTimestamp()));

        TextView locationView = bottomSheetDialog.findViewById(R.id.locationView);
        assert locationView != null;
        Location loc = memo.getLocation();
        locationView.setText(TypeConverters.addressToString(loc.getAddress(), loc.getLatitude(), loc.getLongitude()));

        bottomSheetDialog.show();
    }

}
