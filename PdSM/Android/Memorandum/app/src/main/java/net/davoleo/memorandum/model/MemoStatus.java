package net.davoleo.memorandum.model;

public enum MemoStatus {
    ACTIVE,
    EXPIRED,
    COMPLETE;

    public static MemoStatus byIndex(int index) {
        assert index >= 0 && index < MemoStatus.values().length;
        return MemoStatus.values()[index];
    }
}
