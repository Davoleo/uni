#!/bin/bash

# Independently call envsubst from its exec path
COMMAND=$(which envsubst)
$COMMAND < /etc/httpd/conf/httpd.template.conf > /etc/httpd/conf/httpd.conf

mkdir -p $DOCUMENTROOT
chown apache:apache $DOCUMENTROOT
/usr/sbin/httpd -D FOREGROUND;