package net.davoleo.memorandum.service;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class GeofenceBroadcastReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent)
    {
        GeofencingJobIntentService.enqueueWork(context, intent);
    }
}
