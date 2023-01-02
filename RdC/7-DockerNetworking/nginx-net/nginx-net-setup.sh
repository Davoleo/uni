#!/bin/bash

# Build docker image named nginx-net based Dockerfile in this folder
docker build -t nginx-net .

for i in {2..4}; do
	# Start container with extended privileges custom name, custom mapped port and a bound volume to the web folder here based on nginx-net
	docker run --privileged -d --name "nginx$i" -p "800$i:80" -v "$PWD/../web:/usr/share/nginx/html" nginx-net
	# Start SSH daemon on each container
	docker exec -it nginx$i service ssh start
done