#!/bin/bash

# Variables
NEWUSERSFILE=/tmp/support/newusers

for	ENTRY in $(cat $NEWUSERSFILE); do
	# Extract first, last names and tier fields
	FIRSTNAME=$(echo $ENTRY | cut -d: -f1)
	LASTNAME=$(echo $ENTRY | cut -d: -f2)

	# Account Name
	FIRSTINITIAL=$(echo $FIRSTNAME | cut -c 1 | tr '[:upper]' '[:lower]')
	LOWERLASTNAME=$(echo $LASTNAME | tr '[:upper]' '[:lower]')

	ACCOUNTNAME=$FIRSTINITIAL$LOWERLASTNAME

	# Create account
	userdel $ACCOUNTNAME -rf
	
done

echo "Accounts Removed!"