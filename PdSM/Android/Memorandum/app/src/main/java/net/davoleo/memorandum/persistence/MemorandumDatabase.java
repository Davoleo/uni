package net.davoleo.memorandum.persistence;

import android.content.Context;
import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;
import net.davoleo.memorandum.model.Memo;

@Database(entities = {Memo.class}, version = 1)
public abstract class MemorandumDatabase extends RoomDatabase {

    public static MemorandumDatabase instance;

    public abstract MemoDAO memoDAO();

    public static void init(Context context) {
        instance = Room.databaseBuilder(context, MemorandumDatabase.class, "memo-database").build();
    }
}
