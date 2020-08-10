#!/bin/bash

sudo apt install qt5-default qtpositioning5-dev qtmultimedia5-dev qttools5-dev cmake libqt5svg5-dev

sudo apt install -y libcairo2-dev libagg-dev libpango1.0-dev freeglut3-dev libglm-dev qtlocation5-dev \
                    qml-module-qtpositioning qml-module-qtlocation qtquickcontrols2-5-dev

./scripts/libosmscout.sh