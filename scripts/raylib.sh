#!/bin/bash

if [ "${PWD##*/}" != "carpi" ]; then
  echo "This script should be executed from the carpi directory"
  exit
fi

if [ "$#" == "1" ]; then
  echo "No platform specified"
  exit
fi

./scripts/dependencies.sh

cd /tmp
if [ ! -f "/usr/local/include/raylib.h" ]; then
  wget https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  tar xf 4.0.0.tar.gz
  rm 4.0.0.tar.gz
  mv raylib-4.0.0 raylib
  cd raylib
  if [ -d "build" ]; then
    rm -rf build
  fi
  mkdir build
  cd build
  if [ "$#" == "1" ]; then
    cmake .. -DPLATFORM="$1" -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON
  else
    cmake .. -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON
  fi
  make -j$(nproc)
  sudo make install
  cd /tmp
  rm -rf raylib
fi