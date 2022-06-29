package net.davoleo.memorandum.model;

public enum MemoStatus {
    ACTIVE(0xFFCCDB37),
    EXPIRED(0xFFE53935),
    COMPLETE(0xFF66BB6A);

    private final int color;

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
