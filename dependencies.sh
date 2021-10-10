#!/bin/bash

echo "Updating the system..."
sudo apt update
echo "Upgrading the system..."
sudo apt upgrade -y
echo "Installing dependencies..."
sudo apt install -y build-essential libsdl2-dev cmake
echo "Done"