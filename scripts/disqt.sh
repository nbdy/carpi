#!/bin/bash

if [ ! -f /usr/local/include/disqt/disqt.h ]; then
  cd /tmp/
  git clone https://github.com/smthnspcl/disqt
  cd disqt
  ./build.sh
  cd /tmp/
  rm -rf disqt
fi