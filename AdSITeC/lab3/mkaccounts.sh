#!/bin/bash

# Variables
NEWUSERSFILE=/tmp/support/newusers

for	ENTRY in $(cat $NEWUSERSFILE); do
	# Extract first, last names and tier fields
	FIRSTNAME=$(echo $ENTRY | cut -d: -f1)
	LASTNAME=$(echo $ENTRY | cut -d: -f2)

	# Account Name
	FIRSTINITIAL=$(echo $FIRSTNAME | cut -c 1 | tr '[:upper:]' '[:lower:]')
	LOWERLASTNAME=$(echo $LASTNAME | tr '[:upper:]' '[:lower:]')

	ACCOUNTNAME=$FIRSTINITIAL$LOWERLASTNAME

	# Create account
	useradd $ACCOUNTNAME -c "$FIRSTNAME $LASTNAME"
	
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

