package net.davoleo.memorandum.persistence;

import android.location.Address;
import androidx.room.TypeConverter;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.util.Utils;

import java.util.Date;
import java.util.Locale;

public class TypeConverters {

    //--- Date ---
    @TypeConverter
    public static Date dateFromTimestamp(Long timestamp) {
        return timestamp == null ? null : new Date(timestamp);
    }

    @TypeConverter
    public static Long dateToTimestamp(Date date) {
        return date == null ? null : date.getTime();
    }

    //--- Location ---
    @TypeConverter
    public static Location locationFromString (String serialized) {
        return Location.fromString(serialized);
    }

    @TypeConverter
    public static String locationToString(Location location) {
        return location.toString();
    }

    //--- MemoStatus ---
    @TypeConverter
    public static MemoStatus statusByIndex(int index) {
        return MemoStatus.byIndex(index);
    }

    @TypeConverter
    public static int statusToIndex(MemoStatus status) {
        return status.ordinal();
    }


    public static String addressToString(Address address, double fallbackLatitude, double fallbackLongitude) {
        String locationString = "";

        if (address != null) {
            locationString = Utils.joinStrings(" ",
                    (address.getThoroughfare() != null ? address.getThoroughfare() : ""),
                    (address.getSubThoroughfare() != null ? address.getSubThoroughfare() : ""),
                    (address.getLocality() != null ? address.getLocality() : "")
            );
        }

        if (locationString.isEmpty()) {
            locationString = String.format(
                    Locale.getDefault(),
                    "Lat: %f\nLon: %f",
                    fallbackLatitude,
                    fallbackLongitude
            );
        }

        return locationString;
    }

}
