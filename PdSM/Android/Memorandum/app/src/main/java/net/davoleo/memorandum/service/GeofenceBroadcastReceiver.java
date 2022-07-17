package net.davoleo.memorandum.service;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;
import com.google.android.material.snackbar.Snackbar;

public class GeofenceBroadcastReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent)
    {
        Toast.makeText(context, "Geofence triggered!", Toast.LENGTH_SHORT).show();
        GeofencingJobIntentService.enqueueWork(context, intent);
    }
}
