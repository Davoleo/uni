#!/bin/bash

if [ $# -ne 2 ]; then
    echo "This script requires 2 command-line parameters"
    echo "Usage: $0 <VHOSTNAME> <TIER>"
    exit 1
fi

# Retrieve Command Line Arguments
DOMAIN=$1
TIER=$2

# Configuration file and dir paths
APACHECONF=/etc/apache2/apache2.conf
VHOSTCONFDIR=/etc/apache2/conf.vhosts.d
VHOSTCONF="$VHOSTCONFDIR/$DOMAIN.conf"
WWWROOT=/srv
VHOSTDOCROOT="$WWWROOT/$DOMAIN/www"

case $TIER in
    1)  VHOSTADMIN="basic_support@example.com";;
    2)  VHOSTADMIN="business_support@example.com";;
    3)  VHOSTADMIN="enterprise_support@example.com" ;;
    *)
        echo "Invalid tier specified"
        exit 1
        ;;
esac


mkdir -p /etc/apache2/conf.vhost.d

if [ -e "$VHOSTCONF" ] || [ -d "$VHOSTDOCROOT" ]; then
    echo "$DOMAIN server configuration file or root directory are already present"
    exit 3
fi

grep -q "^IncludeOptional conf\.vhost\.d/\*\.conf$" $APACHECONF

if [ $? -ne 0 ]; then
    # backup before modifying
    cp -a $APACHECONF "$APACHECONF.bak"
    echo "IncludeOptional conf.vhost.d/*.conf" >> $APACHECONF

    if [ $? -ne 0 ]; then
        echo "ERROR: Couldn't append SubConfig folder to Apache Configuration file"
        exit 4
    fi
fi


touch "$DOMAIN.conf"
mkdir -p "/srv/$DOMAIN/www"