#!/bin/bash

cd axoloti/platform_linux
./compile_firmware.sh 2>&1 | tee ../../compile.log
cd ../..
