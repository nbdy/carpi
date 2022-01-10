#!/bin/bash

if [ ! -f /usr/local/include/disqt/disqt.h ]; then
  echo "Installing disqt..."
  cd /tmp/
  git clone https://github.com/smthnspcl/disqt
  cd disqt
  ./build.sh
  cd /tmp/
  rm -rf disqt
  echo "Done."
else
  echo "disqt is already installed."
fi
