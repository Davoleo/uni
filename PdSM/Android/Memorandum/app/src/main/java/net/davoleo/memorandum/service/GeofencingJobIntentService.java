package net.davoleo.memorandum.service;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.text.TextUtils;
import android.util.Log;
import androidx.annotation.NonNull;
import androidx.core.app.JobIntentService;
import androidx.core.app.NotificationCompat;
import androidx.preference.PreferenceManager;
import com.google.android.gms.location.Geofence;
import com.google.android.gms.location.GeofencingEvent;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.TypeConverters;
import net.davoleo.memorandum.ui.MainActivity;

import java.util.ArrayList;
import java.util.List;

public class GeofencingJobIntentService extends JobIntentService {

    private static final int JOB_ID = 0xFF;
    private static final String TAG = "GeofencingJIS";

    public static void enqueueWork(Context context, Intent intent) {
        enqueueWork(context, GeofencingJobIntentService.class, JOB_ID, intent);
    }

    @Override
    protected void onHandleWork(@NonNull Intent intent)
    {
        GeofencingEvent event = GeofencingEvent.fromIntent(intent);
        if (event.hasError()) {
            Log.e(TAG, "onHandleWork: Geofencing Service Error: " + event.getErrorCode());
            return;
        }

        int geofenceTransition = event.getGeofenceTransition();

        if (geofenceTransition == Geofence.GEOFENCE_TRANSITION_ENTER) {
            List<Geofence> triggeredGeofences = event.getTriggeringGeofences();
            ArrayList<String> geoIdList = new ArrayList<>();
            for (Geofence geofence : triggeredGeofences)
                geoIdList.add(geofence.getRequestId());

            sendNotification("You entered: " + TextUtils.join(", ", geoIdList));
        }
    }

    private void sendNotification(String notificationDetails) {
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            String title = getString(R.string.app_name);
            NotificationChannel channel = new NotificationChannel("channel_1", title, NotificationManager.IMPORTANCE_DEFAULT);
            notificationManager.createNotificationChannel(channel);
        }

        //Intent that starts mainActivity
        Intent mainActivityIntent = new Intent(getApplicationContext(), MainActivity.class);

        TaskStackBuilder stackBuilder = TaskStackBuilder.create(this);
        stackBuilder.addParentStack(MainActivity.class);
        stackBuilder.addNextIntent(mainActivityIntent);

        PendingIntent notificationPendingIntent = stackBuilder.getPendingIntent(0, PendingIntent.FLAG_UPDATE_CURRENT);
        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this);
        notificationBuilder.setSmallIcon(R.mipmap.ic_launcher)
                .setColor(MemoStatus.ACTIVE.getColor())
                .setContentTitle(notificationDetails)
                .setContentText(getString(R.string.memo_geofence_entered_notification))
                .setContentIntent(notificationPendingIntent);

        notificationBuilder.setAutoCancel(true);
        notificationManager.notify(0, notificationBuilder.build());
    }

    public static List<Geofence> buildGeofences(Context context, Location... locations) {
        List<Geofence> geofenceList = new ArrayList<>();

        for (Location location : locations)
        {
            Geofence.Builder geofence = new Geofence.Builder();

            if (location.getAddress() == null)
                location.reverseGeocode(context);

            geofence.setRequestId(TypeConverters.addressToString(location.getAddress(), location.getLatitude(), location.getLongitude()));

            SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(context);
            geofence.setCircularRegion(location.getLatitude(), location.getLongitude(), preferences.getInt("location_radius", 30));
            geofence.setTransitionTypes(Geofence.GEOFENCE_TRANSITION_ENTER);
            geofenceList.add(geofence.build());
        }

        return geofenceList;
    }
}
