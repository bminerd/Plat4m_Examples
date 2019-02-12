#! /bin/bash

cmake . -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../Plat4m_CMake/GccArmCortexMToolchain.cmake

make
