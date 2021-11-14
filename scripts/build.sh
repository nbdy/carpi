#!/bin/bash

if [ "${PWD##*/}" != "carpi" ]; then
  echo "This script should be executed from the carpi directory"
  exit
fi

if [ -d "build" ]; then
  rm -rf build
fi
mkdir build
cd build
cmake ..
make -j$(nproc)
