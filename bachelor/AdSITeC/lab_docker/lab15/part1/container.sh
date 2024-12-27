#!/bin/bash

docker run -dP --rm --name fedora_srv -v $PWD/html/index.html:/srv/www/http/index.html fedora_srv