#!/bin/bash

# error_check takes the number of arguments passed on script execute as first and only argument
error_check() {
	local EXITCODE=0;

	if [ $1 -lt 1 ]; then
		echo -n "no parameters passed - "
		EXITCODE=10
	elif [ $1 -gt 5 ]; then
		echo -n "too many arguments (max 5) - "
		EXITCODE=20
	fi

	# If exit code was left unchanged [no error we continue exec]
	if [ $EXITCODE -ne 0 ]; then
		echo "Usage: checkusername.sh <user1> [user2, ..., user5]"
		exit $EXITCODE
	fi
}

error_check $#

for ACCOUNT in "$@"; do
	id "$ACCOUNT" &> /dev/null

	# Id return code is not equal to 0 => user doesn't exist
	if [ $? -ne 0 ]; then
		echo "username $ACCOUNT not found"
	else
		echo "username $ACCOUNT found:"
		id "$ACCOUNT"
		chage -l "$ACCOUNT"
		grep "$ACCOUNT" /etc/passwd
	fi
	echo "-------------"
done
