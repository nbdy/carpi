#!/bin/bash

echo "killing the current carpi instance"
sudo killall carpi
#echo "removing old config files"
#sudo rm /etc/carpi/*
echo "building carpi"
./build.sh
sudo make install