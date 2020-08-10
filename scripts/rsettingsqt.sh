#!/bin/bash

if [ ! -f /usr/local/include/rsettingsqt/rsettingsqt.h ]; then
  cd /tmp/
  git clone https://github.com/smthnspcl/rsettingsqt
  cd rsettingsqt
  ./build.sh
  cd /tmp/
  rm -rf rsettingsqt
fi