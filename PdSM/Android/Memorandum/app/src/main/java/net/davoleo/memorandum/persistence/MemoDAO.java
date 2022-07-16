package net.davoleo.memorandum.persistence;

import androidx.room.*;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;

import java.util.List;

@Dao
public interface MemoDAO {

    @Query("SELECT * FROM Memo")
    List<Memo> getAll();

    @Query("SELECT * FROM Memo WHERE status = :filter")
    List<Memo> getAllOfStatus(MemoStatus filter);

    @Query("SELECT * FROM Memo WHERE status = :filter ORDER BY timestamp ASC")
    List<Memo> getAllOfStatusSorted(MemoStatus filter);

    @Query("SELECT location FROM Memo WHERE status = 0")
    Location[] getActiveLocations();

    @Insert
    void insertOne(Memo memo);

    @Insert
    void insertMany(Memo... memos);

    @Update
    void updateMemo(Memo memo);

    @Delete
    void delete(Memo memo);

}
