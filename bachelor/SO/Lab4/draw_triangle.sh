#!/bin/bash
# Draws a triangle on std output based on a size argument

if [ $# -ne 1 ]
then
    echo 'usage: draw_triangle <size>'
    exit 1
fi

if [ $1 -lt 3 ] || [ $1 -gt 15 ]
then
    echo size must be a number between 3 and 15
    exit 1
fi

# Total rows of the top of the TRYANGLE are 1 less than the size
for i in `seq 1 $(($1 - 1))`  
do
    # First half of the row (looped in reverse order)
    for j in `seq $1 -1 1`
    do
        if [ $j -eq $i ]; then
            echo -n '/'
        else
            echo -n ' '
        fi
    done

    # Second half of the row
    for j in `seq 1 $1` 
    do
        if [ $j -eq $i ]; then
            echo -n '\'
        else
            echo -n ' '
        fi
    done

    # Print new Line
    echo ""
done

# Print trinangle base
for b in `seq 1 $(($1 * 2))`
do
    echo -n '-'
done

echo ""