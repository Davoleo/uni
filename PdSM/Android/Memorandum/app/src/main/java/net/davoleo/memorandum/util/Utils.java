package net.davoleo.memorandum.util;

import android.location.Geocoder;
import android.os.Handler;
import android.os.Looper;

public class Utils {

    public static final Handler MAIN_UI_THREAD_HANDLER = new Handler(Looper.getMainLooper());

    public static Geocoder geocoder;
}
