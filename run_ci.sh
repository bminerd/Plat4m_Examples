#! /bin/bash

set -e

if [ ! -d "gcc-arm-none-eabi-7-2017-q4-major" ]; then
    wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2

    tar xjf gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
fi

./build.sh
