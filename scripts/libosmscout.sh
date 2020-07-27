#!/bin/bash

sudo apt install -y libcairo2-dev libagg-dev libpango1.0-dev freeglut3-dev libglm-dev qtlocation5-dev

cd /tmp/
git clone https://github.com/Framstag/libosmscout
cd libosmscout
mkdir build
cd build
cmake .. -DOSMSCOUT_BUILD_BINDING_JAVA=OFF -DOSMSCOUT_BUILD_TESTS=OFF -DOSMSCOUT_BUILD_DEMOS=OFF
make -j $(nproc)
sudo make install
cd /tmp/
rm -rf libosmscout