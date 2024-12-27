package net.davoleo.memorandum.util;

import android.Manifest;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.location.Geocoder;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import androidx.core.app.ActivityCompat;
import com.google.android.gms.common.api.CommonStatusCodes;
import com.google.android.material.snackbar.Snackbar;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.ui.MainActivity;

import java.util.Calendar;
import java.util.Objects;

import static android.content.Context.MODE_PRIVATE;
import static net.davoleo.memorandum.ui.MainActivity.REQUEST_PERMISSIONS_CODE;

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

    ///////////////////////// Location Permissions
    private static final String LOCATION_PERMISSION =
            Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q ?
                    Manifest.permission.ACCESS_BACKGROUND_LOCATION :
                    Manifest.permission.ACCESS_FINE_LOCATION;

    public static boolean hasLocationPermissions(Context context) {
        int permissionCode = ActivityCompat.checkSelfPermission(context, LOCATION_PERMISSION);
        return permissionCode == PackageManager.PERMISSION_GRANTED;
    }

    public static void requestLocationPermissions(MainActivity mainRef, View snackbarHolder) {

        boolean shouldProvideRationale =
                ActivityCompat.shouldShowRequestPermissionRationale(mainRef, LOCATION_PERMISSION);

        if (shouldProvideRationale) {
            Snackbar bar = Snackbar.make(snackbarHolder, mainRef.getString(R.string.location_permission_rationale), Snackbar.LENGTH_LONG);
            bar.setAction(android.R.string.ok, v ->
                    ActivityCompat.requestPermissions(mainRef, new String[]{LOCATION_PERMISSION}, REQUEST_PERMISSIONS_CODE));
            bar.show();
        }
        else {
            ActivityCompat.requestPermissions(mainRef, new String[]{LOCATION_PERMISSION}, REQUEST_PERMISSIONS_CODE);
        }
    }


    ///////////////////////// Dialog

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

    ///////////////////////////////////// MISC

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
