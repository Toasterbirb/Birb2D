#!/bin/sh

BUILD_DIR="./build"

# Delete any existing build directories
[ -d "$BUILD_DIR" ] && rm -rv "$BUILD_DIR"

# Create a fresh build directory and move into it
mkdir -pv "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DRELEASE=on -DWINDOWS=on -DTESTS=off -DUTILS=off -DSTATIC_SDL=on -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_C_FLAGS=-fstack-protector -DCMAKE_CXX_FLAGS=-fstack-protector -DMINGW=TRUE

# Compile
make -j$(nproc)
