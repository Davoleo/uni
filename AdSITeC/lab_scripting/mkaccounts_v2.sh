#!/bin/bash

# Variables
NEWUSERSFILE=/tmp/support/newusers

# Command Line argument
OPTION=$1

case $OPTION in
	'')
		;;
	-v)
		VERBOSE=y
		;;
	-h)
		echo "Usage: mkaccounts.sh [-h|-v]"
		exit 0
		;;
	*)
		echo "Usage: mkaccounts.sh [-h|-v]"
		exit 1
		;;
esac

for	ENTRY in $(cat $NEWUSERSFILE); do
	# Extract first, last names and tier fields
	FIRSTNAME=$(echo $ENTRY | cut -d: -f1)
	LASTNAME=$(echo $ENTRY | cut -d: -f2)

	# Account Name
	FIRSTINITIAL=$(echo $FIRSTNAME | cut -c 1 | tr '[:upper:]' '[:lower:]')
	LOWERLASTNAME=$(echo $LASTNAME | tr '[:upper:]' '[:lower:]')

	ACCOUNTNAME=$FIRSTINITIAL$LOWERLASTNAME

	ACCTEXISTS=''
	EXISTING_FULLNAME=''
	
	if id "$ACCOUNTNAME" &> /dev/null; then
		ACCTEXISTS='y'
		EXISTING_FULLNAME="$(grep ^$ACCOUNTNAME: /etc/passwd | cut -f5 -d:)"
	fi

	if [ "$ACCTEXISTS" = 'y' ]; then
		if [ "$EXISTING_FULLNAME" = "$FIRSTNAME $LASTNAME" ]; then
			echo "Skipping $ACCOUNTNAME... (Duplicate Found)"
		else
			echo "Skipping $ACCOUNTNAME... (Conflict Found)"
		fi
	else
		# Create account
		useradd $ACCOUNTNAME -c "$FIRSTNAME $LASTNAME"
		if [ "$VERBOSE" = 'y' ]; then
			echo "Created Account: $ACCOUNTNAME"
		fi
	fi
	
done

TOTAL=$(wc -l < $NEWUSERSFILE)

TIER1COUNT=$(grep -c :1$ $NEWUSERSFILE)
TIER2COUNT=$(grep -c :2$ $NEWUSERSFILE)
TIER3COUNT=$(grep -c :3$ $NEWUSERSFILE)

TIER1RATIO=$(( $TIER1COUNT * 100 / $TOTAL))
TIER2RATIO=$(( $TIER2COUNT * 100 / $TOTAL))
TIER3RATIO=$(( $TIER3COUNT * 100 / $TOTAL))

# print report 
echo "\"Tier 1\", \"$TIER1COUNT\", \"$TIER1RATIO%\""
echo "\"Tier 2\", \"$TIER2COUNT\", \"$TIER2RATIO%\""
echo "\"Tier 3\", \"$TIER3COUNT\", \"$TIER3RATIO%\""

