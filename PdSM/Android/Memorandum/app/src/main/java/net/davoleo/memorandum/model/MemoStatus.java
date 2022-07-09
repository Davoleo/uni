package net.davoleo.memorandum.model;

import androidx.annotation.ColorInt;
import androidx.annotation.DrawableRes;
import androidx.annotation.Nullable;
import net.davoleo.memorandum.R;

public enum MemoStatus {
    ACTIVE(0xFFCCDB37, R.drawable.ic_schedule),
    EXPIRED(0xFFE53935, R.drawable.ic_warning),
    COMPLETE(0xFF66BB6A, R.drawable.ic_done);

    @ColorInt
    private final int color;

    @DrawableRes
    private final int icon;

    public static final String[] NAMES = { ACTIVE.name(), EXPIRED.name(), COMPLETE.name() };

    MemoStatus(int color, @DrawableRes int icon)
    {
        this.color = color;
        this.icon = icon;
    }

    public int getColor()
    {
        return color;
    }

    @DrawableRes
    public int getIcon()
    {
        return icon;
    }

    @Nullable
    public static MemoStatus byIndex(int index) {
        if (index >= 0 && index < MemoStatus.values().length)
            return MemoStatus.values()[index];
        else
            return null;
    }
}
