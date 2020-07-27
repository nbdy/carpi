#!/bin/bash

if [ ! -d "build" ]; then mkdir build; fi
cd build
if [ $1 == "debug" ]; then cmake .. -DDEBUG=ON; fi
make -j"$(nproc)"
for m in modules/*/lib*.so; do
  cp "$m" .
done