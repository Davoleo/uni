#!/bin/bash

# Independently call envsubst from its exec path
COMMAND=$(which envsubst)

cd /var/www/html
$COMMAND < Hello_docker.html > index.html
/usr/sbin/httpd -D FOREGROUND;