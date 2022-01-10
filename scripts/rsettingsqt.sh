#!/bin/bash

if [ ! -f /usr/local/include/rsettingsqt/rsettingsqt.h ]; then
  echo "Installing rsettingsqt"
  cd /tmp/
  git clone https://github.com/smthnspcl/rsettingsqt
  cd rsettingsqt
  echo "Building rsettingsqt"
  ./build.sh
  cd /tmp/
  rm -rf rsettingsqt
  echo "rsettingsqt installed"
else
  echo "rsettingsqt already installed"
fi