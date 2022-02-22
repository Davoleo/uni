#!/bin/bash
# Lists all files in the given directory grouped by file size categories
# Categories: <= 1KB | <= 1MB | <= 1GB | > 1GB

if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo 'usage: file_sizes <directory>'
    exit 1
fi

b_fcount=0
kb_fcount=0
mb_fcount=0
gb_fcount=0

# For all files in the directory (/*)
for file in $1/*
do
    # Check if
    if test -r $file -a -f $file
    then
        size=`wc -c <$file`
        if [ $size -le 1000 ]; then
            ((b_fcount++))
        elif [ $size -le 1000000 ]; then
            ((kb_fcount++))
        elif [ $size -le 1000000000 ]; then
            ((mb_fcount++))
        else
            ((gb_fcount++))
        fi
    fi
done

printf "%d files take less than 1KB of space\n" $b_fcount
printf "%d files take less than 1MB of space\n" $kb_fcount
printf "%d files take less than 1GB of space\n" $mb_fcount
printf "%d files take more than 1GB of space\n" $gb_fcount
