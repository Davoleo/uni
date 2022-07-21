package net.davoleo.memorandum.service;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;
import androidx.core.app.NotificationCompat;
import com.google.android.gms.location.Geofence;
import com.google.android.gms.location.GeofencingEvent;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.persistence.TypeConverters;
import net.davoleo.memorandum.ui.MainActivity;

import java.util.List;

public class GeofenceBroadcastReceiver extends BroadcastReceiver {

    private static final String TAG = "GeofenceReceiver";

    @Override
    public void onReceive(Context context, Intent intent)
    {
        //Debug Toast
        //Toast.makeText(context, "Geofence triggered!", Toast.LENGTH_SHORT).show();

        GeofencingEvent event = GeofencingEvent.fromIntent(intent);
        if (event.hasError()) {
            Log.e(TAG, "onHandleWork: Geofencing Service Error: " + event.getErrorCode());
            return;
        }

        int geofenceTransition = event.getGeofenceTransition();
        List<Geofence> triggeredGeofences = event.getTriggeringGeofences();

        if (triggeredGeofences != null && geofenceTransition == Geofence.GEOFENCE_TRANSITION_ENTER) {

            for (Geofence geofence : triggeredGeofences) {
                Location location = TypeConverters.locationFromString(geofence.getRequestId());
                location.reverseGeocode(context);
                sendNotification(context, location);
            }
        }
    }

    private void sendNotification(Context context, Location location) {
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(context);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            String title = context.getString(R.string.app_name);
            NotificationChannel channel = new NotificationChannel("channel_1", title, NotificationManager.IMPORTANCE_DEFAULT);
            notificationManager.createNotificationChannel(channel);
            notificationBuilder.setChannelId(channel.getId());
        }

        //Intent that starts mainActivity
        Intent mainActivityIntent = new Intent(context, MainActivity.class);

        TaskStackBuilder stackBuilder = TaskStackBuilder.create(context);
        stackBuilder.addParentStack(MainActivity.class);
        stackBuilder.addNextIntent(mainActivityIntent);

        PendingIntent notificationPendingIntent = stackBuilder.getPendingIntent(0, PendingIntent.FLAG_UPDATE_CURRENT);

        String placeName = TypeConverters.addressToString(location.getAddress(), location.getLatitude(), location.getLongitude());
        Memo memo = MemorandumDatabase.instance.memoDAO().getMemoByLocation(location);

        notificationBuilder.setSmallIcon(R.mipmap.ic_launcher)
                .setColor(MemoStatus.ACTIVE.getColor())
                .setContentTitle(placeName)
                .setContentText(String.format(context.getString(R.string.memo_geofence_entered_notification), memo != null ? memo.title : placeName))
                .setContentIntent(notificationPendingIntent);

        notificationBuilder.setAutoCancel(true);
        notificationManager.notify(0, notificationBuilder.build());
    }
}
