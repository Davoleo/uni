package net.davoleo.memorandum.model;

import android.graphics.Color;

public enum MemoStatus {
    ACTIVE(0xFF00FF00),
    EXPIRED(0xFFFFFF00),
    COMPLETE(0x0000FFFF);

    private int color;

    MemoStatus(int color)
    {
        this.color = color;
    }

    public int getColor()
    {
        return color;
    }

    public static MemoStatus byIndex(int index) {
        assert index >= 0 && index < MemoStatus.values().length;
        return MemoStatus.values()[index];
    }
}
