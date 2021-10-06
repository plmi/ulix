#!/bin/bash

CONTAINER=ulix-dev
DIRECTORY=$(readlink -f $1)
docker run --platform linux/386 --privileged -it --rm -v "${DIRECTORY}:/root/ulix" "$CONTAINER"
