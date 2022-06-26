package net.davoleo.memorandum.model;

import android.location.Geocoder;

public class Location {

    private final double longitude;
    private final double latitude;

    private transient String name;

    public Location(double longitude, double latitude)
    {
        this.longitude = longitude;
        this.latitude = latitude;

    }
}
