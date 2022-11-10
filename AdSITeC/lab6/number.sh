#!/bin/bash

# Handle usage error
if [ $# -lt 1 ]; then
	echo "Usage: number.sh <num>"
	exit 1
fi

ISNUMBER_REGEX="^[0-9]+$"
NUMBER=$1

# Test if number conforms to Regular Expression that checks if it's an integer
if [[ $NUMBER =~ $ISNUMBER_REGEX ]]; then
	if [ $NUMBER -gt 100 ]; then
		echo "greater than 100"
	else
		echo "less or equal than 100"
	fi
else
	echo "not a number!!"
fi