#!/bin/bash

BUILD_DIR="$(dirname $0)/../build_win"
echo "Building to $BUILD_DIR"

# Delete any existing build directories
[ -d "$BUILD_DIR" ] && rm -rv "$BUILD_DIR"

# Create a fresh build directory and move into it
mkdir -pv "$BUILD_DIR"
cd $BUILD_DIR

if [ "$1" == "test" ]
then
	cmake .. -DRELEASE=on -DTESTS=on -DWINDOWS=on -DUTILS=off -DSTATIC_SDL=on -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc-posix -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++-posix -DCMAKE_C_FLAGS=-fstack-protector -DCMAKE_CXX_FLAGS=-fstack-protector -DMINGW=TRUE
else
	cmake .. -DRELEASE=on -DTESTS=off -DWINDOWS=on -DUTILS=off -DSTATIC_SDL=on -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_C_FLAGS=-fstack-protector -DCMAKE_CXX_FLAGS=-fstack-protector -DMINGW=TRUE
fi
