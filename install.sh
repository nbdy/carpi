#!/bin/bash

if [ ! -d "build" ]; then
    echo "you need to build the project first"
    echo "./build.sh would be a good start"
    exit
fi

cd build
sudo make install

echo "carpi is installed now"