BEGIN {
    print "Scanning file"
}

{
    printf "line %d: %s\n", NR, $0;
    lineCount++;
    wordCount+=NF;
}

END {
    printf "lines=%d, words=%d\n", lineCount, wordCount
}