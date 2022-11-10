#!/bin/bash

usage() {
	echo "Usage: index.sh \"<string>\" <append|new>";
	exit 1;
}

# Argument Check
if [ $# -lt 2 ]; then 
	usage
fi

# Input Variables
STRING=$1
COMMAND=$2

# Command Switch
case $COMMAND in
	new)
	echo -n "$STRING" > ./index.html
	;;
	append)
	echo -n "$STRING" >> ./index.html
	;;
	*)
	usage
	;;
esac