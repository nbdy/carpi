#!/bin/bash

if [ ! $(id -u) -ne 0 ]; then
    echo "please dont run as root"
    exit
fi

RPI="OFF"

if [ -f /sys/firmware/devicetree/base/model ]; then
  echo "building for raspberry pi"
  RPI="ON"
else
  echo "building for desktop"
fi
if [ "$RPI" == "ON" ]; then
  THREADS=${1:-4}
else
  THREADS=${1:-8}
fi

echo "make'ing with $THREADS threads"

workingDir=$(pwd)

echo "------------------------------------------------ UPDATING"
sudo apt update
echo "------------------------------------------------ UPGRADING"
sudo apt upgrade -y
echo "------------------------------------------------ INSTALLING DEPS"

sudo apt install -y git build-essential libgps-dev gcc libsndfile-dev libcurl4-openssl-dev libmpg123-dev libao-dev \
                    libssl-dev zlib1g-dev libbz2-dev autoconf libpcap-dev gpsd gpsd-clients libbluetooth-dev unzip \
                    libicu-dev clang postgresql mapnik-utils aircrack-ng libpq-dev postgis tmux cmake libprotobuf-dev\
                    libpstreams-dev libharfbuzz-dev libjpeg-dev libtiff-dev libwebp-dev libboost-all-dev libsqlite3-dev \
                    sqlite3 libmapbox-variant-dev

cd $workingDir

if [ ! -x "$(command -v protoc)" ]; then
  echo "------------------------------------------------ INSTALLING PROTOBUF 3.7.1"
  cd /tmp/
  if [ -d "protobuf-3.7.1" ]; then
    rm -rf protobuf-3.7.1
  fi
  echo "downloading"
  wget https://github.com/protocolbuffers/protobuf/releases/download/v3.7.1/protobuf-cpp-3.7.1.tar.gz > /dev/null 2>&1
  echo "unpacking"
  tar xf protobuf-cpp-3.7.1.tar.gz > /dev/null 2>&1
  rm protobuf-cpp-3.7.1.tar.gz
  cd protobuf-3.7.1/
  echo "running autogen.sh"
  ./autogen.sh > /dev/null 2>&1
  echo "running configure"
  ./configure > /dev/null 2>&1
  echo "building"
  make -j "$THREADS" > /dev/null 2>&1
  echo "installing"
  sudo make install > /dev/null 2>&1
  echo "cleaning up"
  cd /tmp/
  rm -rf protobuf-3.7.1/
  echo "linking"
  if [ ! -f "/usr/lib/libprotobuf.so" ]; then
    sudo ln -s /usr/local/lib/libprotobuf.so /usr/lib/libprotobuf.so
  fi
else
  echo "------------------------------------------------ PROTOBUF ALREADY INSTALLED"
fi

echo "------------------------------------------------ INSTALLING EXTRA DEPENDENCIES"
if [ "$RPI" == "ON" ]; then
  echo "rpi does not need any extra dependencies"
else
  echo "installing desktop dependencies"
  sudo apt install -y libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev \
                      libglu1-mesa-dev > /dev/null 2>&1
fi

cd $workingDir

if [ ! -f "/usr/local/include/raylib.h" ]; then
  echo "------------------------------------------------ INSTALLING RAYLIB"
  cd /tmp/
  if [ -d "raylib" ]; then
    rm -rf raylib
  fi
  git clone https://github.com/raysan5/raylib
  cd raylib
  mkdir build
  cd build
  cmake ..
  if [ "$RPI" == "ON" ]; then
    echo "compiling raylib for rpi"
    make PLATFORM=PLATFORM_RPI -j "$THREADS"
  else
    echo "compiling raylib for desktop"
    make PLATFORM=PLATFORM_DESKTOP -j "$THREADS"
  fi
  sudo make install
  cd /tmp/
  rm -rf raylib
else
  echo "------------------------------------------------ RAYLIB ALREADY INSTALLED"
fi

cd $workingDir

if [ ! -d "/usr/local/share/proj" ]; then
  echo "------------------------------------------------ INSTALLING PROJ"
  cd /tmp/
  if [ -d "proj-7.0.1" ]; then
    rm -rf proj-7.0.1
  fi
  wget https://download.osgeo.org/proj/proj-7.0.1.tar.gz
  tar xf proj-7.0.1.tar.gz
  rm proj-7.0.1.tar.gz
  cd proj-7.0.1/
  ./configure
  make -j "$THREADS"
  sudo make install
else
  echo "------------------------------------------------ PROJ ALREADY INSTALLED"
fi

cd $workingDir

if [ ! -d "/usr/local/include/mapnik/" ]; then
  echo "------------------------------------------------ INSTALLING MAPNIK"
  cd /tmp/
  if [ -d "mapnik" ]; then
    rm -rf mapnik
  fi
  git clone https://github.com/mapnik/mapnik
  cd mapnik
  git checkout v3.0.23
  git submodule update --init deps/mapbox/variant
  git submodule update --init
  ./bootstrap.sh
  ./configure
  make -j "$THREADS"
  sudo make install
  cd /tmp
else
  echo "------------------------------------------------ MAPNIK IS ALREADY INSTALLED"
fi

cd $workingDir

echo "------------------------------------------------ INITIALIZING SUBMODULES"
git submodule init > /dev/null 2>&1
echo "------------------------------------------------ UPDATING SUBMODULES"

git submodule update --init --recursive --remote > /dev/null 2>&1

echo "------------------------------------------------ SETTING UP MBTILES-CPP"
cd mbtiles-cpp
./setup.sh > /dev/null 2>&1

cd $workingDir

echo "------------------------------------------------ CONFIGURING DYNAMIC LINKER RUN-TIME BINDINGS"
sudo ldconfig