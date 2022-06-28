package net.davoleo.memorandum.model;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

import java.util.Date;

@Entity
public class Memo {

    @PrimaryKey(autoGenerate = true)
    @ColumnInfo(name = "uid")
    public int uniqueId = 0;

    private Date timestamp;
    private Location location;

    public String title;
    public String description;

    public MemoStatus status;

    public Memo(String title, String description, MemoStatus status)
    {
        this.title = title;
        this.description = description;
        this.status = status;
    }

    public Date getTimestamp()
    {
        return timestamp;
    }

    public void setTimestamp(Date timestamp)
    {
        this.timestamp = timestamp;
    }

    public Location getLocation()
    {
        return location;
    }

    public void setLocation(Location location)
    {
        this.location = location;
    }
}
