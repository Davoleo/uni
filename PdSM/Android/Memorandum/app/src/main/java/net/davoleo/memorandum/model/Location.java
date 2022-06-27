package net.davoleo.memorandum.model;

import android.annotation.SuppressLint;
import androidx.annotation.NonNull;

public class Location {

    private final double longitude;
    private final double latitude;

    private transient String name;

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
}
