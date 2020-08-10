#!/bin/bash

if [ ! -f /usr/local/lib/libosmscout.so ]; then
  cd /tmp/
  if [ ! -d libosmscout ]; then
    git clone https://github.com/smthnspcl/libosmscout
  fi
  cd libosmscout
  mkdir build
  cd build
  cmake .. -DOSMSCOUT_BUILD_BINDING_JAVA=OFF -DOSMSCOUT_BUILD_TESTS=OFF -DOSMSCOUT_BUILD_DEMOS=OFF
  make -j "$(nproc)"
  sudo make install
  cd /tmp/
  rm -rf libosmscout
fi