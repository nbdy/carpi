#!/bin/bash

if [ "${PWD##*/}" != "carpi" ]; then
  echo "This script should be executed from the carpi directory"
  exit
fi

if [ "$1" == "crosscompile" ] && [ $# == 1 ]; then
  echo "No platform specified"
  exit
fi

./scripts/dependencies.sh

cd ext
if [ ! -d "raylib" ]; then
  wget https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  tar xf 4.0.0.tar.gz
  rm 4.0.0.tar.gz
  mv raylib-4.0.0 raylib
fi
cd raylib
if [ -d "build" ]; then
  rm -rf build
fi
mkdir build
cd build
if [ "$1" == "crosscompile" ]; then
  cmake .. -DPLATFORM="$2" -DCMAKE_C_COMPILER=/usr/bin/arm-linux-gnueabihf-gcc -DCMAKE_CXX_COMPILER=/usr/bin/arm-linux-gnueabihf-g++ -DBUILD_EXAMPLES=OFF
else
  cmake .. -DBUILD_EXAMPLES=OFF
fi
make -j8
