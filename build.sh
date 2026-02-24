#!/bin/bash

# Change directory to .sh file location
cd $(dirname $0)

# CMake Build Type
BUILD_TYPE=Debug

# Configure project
cmake -S . -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_INSTALL_PREFIX=dist

# Build project
cmake --build build --config $BUILD_TYPE -j $((`nproc` - 1))

# cmake --install build >> /dev/null
