package net.davoleo.memorandum.persistence;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;
import net.davoleo.memorandum.model.Memo;

import java.util.List;

@Dao
public interface MemoDAO {

    @Query("SELECT * FROM Memo")
    List<Memo> getAll();

    @Insert
    void insertOne(Memo memo);

    @Insert
    void insertMany(Memo... memos);

    @Delete
    void delete(Memo memo);

}
