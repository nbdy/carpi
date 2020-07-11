#!/bin/bash

if [ ! $(id -u) -ne 0 ]; then
    echo "please dont run as root"
    exit
fi

THREADS="${1:-0}"

git pull origin master
git submodule update --init --recursive --remote

if [ -d build/ ]; then
    rm -rf build/
fi

mkdir build
cd build/
cmake ..
if [ -f /sys/firmware/devicetree/base/model ]; then
    echo "building for raspberry pi"
    THREADS=2
else
    echo "building for X11 system"
    THREADS=8
fi

if [ "$THREADS" == 0 ]; then
  THREADS=4
fi

echo "building with $THREADS threads"
make -j "$THREADS"