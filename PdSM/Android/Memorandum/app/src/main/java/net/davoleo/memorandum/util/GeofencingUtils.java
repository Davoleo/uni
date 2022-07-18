package net.davoleo.memorandum.util;

import android.app.PendingIntent;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.Log;
import androidx.annotation.Nullable;
import androidx.preference.PreferenceManager;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.location.*;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.persistence.TypeConverters;
import net.davoleo.memorandum.service.GeofenceBroadcastReceiver;

import java.util.Arrays;

public class GeofencingUtils extends ContextWrapper {

    private static final String TAG = "GeofencingUtils";
    public static final int GEOFENCE_BROADCAST_REQUEST_CODE = 0;

    public final GeofencingClient client;

    private PendingIntent pendingIntent;

    private static final int PENDING_INTENT_FLAGS = Build.VERSION.SDK_INT >= Build.VERSION_CODES.S ?
            PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_MUTABLE :
            PendingIntent.FLAG_UPDATE_CURRENT;

    public GeofencingUtils(Context base)
    {
        super(base);
        client = LocationServices.getGeofencingClient(base);
    }

    public GeofencingRequest createGeofencingRequest(Geofence... geofences) {

        if (geofences.length <= 0)
            return null;

        GeofencingRequest.Builder request = new GeofencingRequest.Builder();
        request.setInitialTrigger(GeofencingRequest.INITIAL_TRIGGER_ENTER);

        if (geofences.length == 1)
            request.addGeofence(geofences[0]);
        else
            request.addGeofences(Arrays.asList(geofences));

        return request.build();
    }

    public Geofence createGeofence(Location location) {

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        return new Geofence.Builder()
                .setCircularRegion(location.getLatitude(), location.getLongitude(), prefs.getInt("location_radius", 200))
                .setRequestId(TypeConverters.locationToString(location))
                .setTransitionTypes(Geofence.GEOFENCE_TRANSITION_ENTER)
                .setExpirationDuration(Geofence.NEVER_EXPIRE)
                .build();
    }

    public PendingIntent getPendingIntent()
    {
        if (pendingIntent == null)
        {
            Intent intent = new Intent(this, GeofenceBroadcastReceiver.class);
            pendingIntent = PendingIntent.getBroadcast(this, GEOFENCE_BROADCAST_REQUEST_CODE, intent, PENDING_INTENT_FLAGS);
        }

        return pendingIntent;
    }

    ////////////////////////////// STATIC UTILITIES /////////////////////////////////////////

    public static String getErrorString(Exception e) {
        if (e instanceof ApiException) {
            ApiException exception = (ApiException) e;
            switch (exception.getStatusCode()) {
                case GeofenceStatusCodes.GEOFENCE_NOT_AVAILABLE:
                    return "Geofence not Available!";
                case GeofenceStatusCodes.GEOFENCE_TOO_MANY_GEOFENCES:
                    return "Too Many Locations to monitor (Maximum is 100)";
                case GeofenceStatusCodes.GEOFENCE_TOO_MANY_PENDING_INTENTS:
                    return "Too many pending intents!";
            }
        }

        return e.getLocalizedMessage();
    }

    public static void debugLogGeofencingTask(@Nullable Object nullOrException) {
        if (nullOrException == null) {
            Log.d(TAG, "onSuccess: Geofence Monitoring changed succesfully");
        }
        else if (nullOrException instanceof Exception) {
            Log.d(TAG,"onFailure: Geofence Monitoring change FAILED:\t" + getErrorString((Exception) nullOrException));
        }
    }
}
