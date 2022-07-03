package net.davoleo.memorandum.util;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.location.Geocoder;
import android.os.Handler;
import android.os.Looper;

import java.util.Calendar;

public class Utils {

    public static final Handler MAIN_UI_THREAD_HANDLER = new Handler(Looper.getMainLooper());

    public static Geocoder geocoder;

    public static void showDateTimePickerDialog(Context context, DateTimeConsumer consumer) {

        Calendar calendar = Calendar.getInstance();

        DatePickerDialog datePicker = new DatePickerDialog(context, (dateView, year, month, day) -> {
            TimePickerDialog timePicker = new TimePickerDialog(
                    context,
                    (timeView, hour, minute) -> consumer.apply(year, month, day, hour, minute),
                    calendar.get(Calendar.HOUR_OF_DAY),
                    calendar.get(Calendar.MINUTE),
                    true
            );

            timePicker.show();
        }, calendar.get(Calendar.YEAR), calendar.get(Calendar.MONTH), calendar.get(Calendar.DAY_OF_MONTH));


        datePicker.show();
    }
}
