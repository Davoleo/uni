package net.davoleo.memorandum.persistence;

import androidx.room.TypeConverter;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.MemoStatus;

import java.util.Date;

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


}
