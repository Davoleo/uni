#!/bin/bash
# Lists files in the specified directory that have size in bytes less than the second argument

if [ $# -ne 2 ] || [ ! -d $1 ]
then
    echo 'usage: listfiles <dirpath> <size>'
    exit 1
fi

for i in $1/* 
do
    if test -r $i -a -f $i
    then
        size=`wc -c <$i`
        if test $size -lt $2
        then
            echo `basename $i` has size $size bytes
        fi
    fi
done

exit 0

