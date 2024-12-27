package net.davoleo.memorandum.model;

import android.annotation.SuppressLint;
import android.content.Context;
import android.location.Address;
import android.util.Log;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import net.davoleo.memorandum.util.Utils;

import java.io.IOException;
import java.util.List;

public class Location {

    private static final String TAG = "Location";
    private final double longitude;
    private final double latitude;

    @Nullable
    private Address address;

    public Location(double longitude, double latitude)
    {
        this.longitude = longitude;
        this.latitude = latitude;
    }

    @SuppressLint("DefaultLocale")
    @NonNull
    @Override
    public String toString()
    {
        return String.format("%f^%f", longitude, latitude);
    }

    public static Location fromString(String location) throws NumberFormatException {
        String[] splitLocation = location.split("\\^");
        return new Location(Double.parseDouble(splitLocation[0]), Double.parseDouble(splitLocation[1]));
    }

    public boolean reverseGeocode(Context context) {
        try
        {
            List<Address> addresses = Utils.getGeocoder(context).getFromLocation(this.latitude, this.longitude, 1);
            if (addresses.isEmpty())
                return false;

            this.address = addresses.get(0);
            return true;
        }
        catch (IOException e)
        {
            this.address = null;
            Log.w(TAG, "reverseGeocode: Error when reverseGeocoding location: lat: " + this.latitude + ", lon: " + this.longitude);
        }

        return false;
    }

    @Override
    public boolean equals(@Nullable Object obj)
    {
        if (obj instanceof Location) {
            Location otherLoc = (Location) obj;

            return this.longitude == otherLoc.longitude &&
                    this.latitude == otherLoc.latitude;
        }

        return false;
    }

    @Nullable
    public Address getAddress()
    {
        return address;
    }

    public double getLatitude()
    {
        return latitude;
    }

    public double getLongitude()
    {
        return longitude;
    }
}
