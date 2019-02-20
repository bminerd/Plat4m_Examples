#! /bin/bash

set -e

cd Blinky_STM32F30x_App
./build.sh
cd ..

cd Blinky_STM32F4xx_App
./build.sh
cd ..

cd Blinky_SystemLite_STM32F30x_App
./build.sh
cd ..
