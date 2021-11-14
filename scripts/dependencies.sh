#!/bin/bash

PLATFORM="DESKTOP"
if [ "$#" == "1" ]; then
  PLATFORM="$1"
fi

echo "Updating the system..."
sudo apt update
echo "Upgrading the system..."
sudo apt upgrade -y
echo "Installing dependencies..."
sudo apt-get install -y libdrm-dev libegl1-mesa-dev libgles2-mesa-dev libgbm-dev libodbc1 libmapnik-dev
if [ "$PLATFORM" == "PI4" ]; then
  sudo apt install -y libraspberrypi-dev raspberrypi-kernel-headers
fi
echo "Done"