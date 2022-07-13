package net.davoleo.memorandum.util;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.SharedPreferences;
import android.location.Geocoder;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import net.davoleo.memorandum.R;

import java.util.Calendar;
import java.util.Objects;

import static android.content.Context.MODE_PRIVATE;

public class Utils {

    public static final Handler MAIN_UI_THREAD_HANDLER = new Handler(Looper.getMainLooper());

    private static Geocoder geocoder;
    public static Geocoder getGeocoder(Context context) {
        if (geocoder == null) {
            //Initialize Geocoder
            geocoder = new Geocoder(context);
        }

        return geocoder;
    }

    //PREFERENCES
    private static SharedPreferences preferences;
    public static SharedPreferences getSharedPreferences(Context context) {
        if (preferences == null) {
            //Init shared preferences
            preferences = context.getSharedPreferences(context.getString(R.string.memorandum_shared_prefs), MODE_PRIVATE);
        }
        return preferences;
    }

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

    //////////////////////////////////////////////////////////////

    public static String joinStrings(CharSequence delimiter, CharSequence... elements) {
        Objects.requireNonNull(delimiter);
        Objects.requireNonNull(elements);

        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < elements.length; i++)
        {
            CharSequence element = elements[i];
            builder.append(element);

            if (i+1 < elements.length)
                builder.append(delimiter);
        }

        return builder.toString();
    }

    public static <T> int indexOf(T[] array, T key) {
        for (int i = 0; i < array.length; i++)
        {
            if (array[i].equals(key))
                return i;
        }

        return -1;
    }

    public static int convertDpToPx(Context context, int dp){
        return Math.round(dp * (context.getResources().getDisplayMetrics().xdpi / DisplayMetrics.DENSITY_DEFAULT));
    }

}
