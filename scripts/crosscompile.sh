#!/bin/bash

sudo apt install -y gcc-arm-linux-gnueabihf cpp-arm-linux-gnueabihf

export CC=/usr/bin/arm-linux-gnueabihf-gcc
export CXX=/usr/bin/arm-linux-gnueabihf-g++
./raylib.sh