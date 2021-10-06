#!/bin/bash

CONTAINER="ulix-dev"
docker image rm "$CONTAINER"
docker build --no-cache -t "$CONTAINER" .
