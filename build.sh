#!/bin/bash

THREADS="8"

if [ -f "/sys/firmware/devicetree/base/model" ]; then
  THREADS="4"
fi

if [ -d "build" ]; then
  rm -rf build
fi

mkdir build
cd build
cmake ..
make -j"$THREADS"
sudo make install