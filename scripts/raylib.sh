#!/bin/bash

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
  sudo ln -s /usr/local/lib/libraylib.so.4.0.0 /usr/lib/libraylib.so.400
  cd /tmp
  rm -rf raylib
fi