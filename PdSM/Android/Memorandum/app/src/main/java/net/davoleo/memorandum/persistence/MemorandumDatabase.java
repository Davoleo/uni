package net.davoleo.memorandum.persistence;

import android.content.Context;
import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;
import androidx.room.TypeConverters;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;

import java.util.Date;

@Database(entities = {Memo.class}, version = 1, exportSchema = false)
@TypeConverters({net.davoleo.memorandum.persistence.TypeConverters.class})
public abstract class MemorandumDatabase extends RoomDatabase {

    public static MemorandumDatabase instance;

    public abstract MemoDAO memoDAO();

    public static void init(Context context) {
        instance = Room.databaseBuilder(context, MemorandumDatabase.class, "memo-database").build();

        //Thread thread = new Thread(() -> instance.memoDAO().insertMany(
        //        new Memo("Test0", "aaaaaaaaaaa", MemoStatus.COMPLETE, new Date(), new Location(33, 44)),
        //        new Memo("Test1", "bbbbbbbbbbbbbbbbbbb", MemoStatus.ACTIVE, new Date(), new Location(44, 33)),
        //        new Memo("Test2", "ccc", MemoStatus.COMPLETE, new Date(), new Location(33, 33)),
        //        new Memo("Test3", "MATPAC", MemoStatus.EXPIRED, new Date(), new Location(44, 44))
        //));
        //thread.start();
    }
}
