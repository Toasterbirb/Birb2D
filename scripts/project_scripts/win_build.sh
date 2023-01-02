#!/bin/sh

# Drag and drop script for compiling Birb2D projects for
# windows. Just copy paste the script to the root of the
# project directory and run the script.
#
# A build_win directory will be created and the make
# files generated should result in a working .exe file

BUILD_DIR="./build_win"

# Create a fresh build directory and move into it
mkdir -pv "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DRELEASE=on -DWINDOWS=on -DTESTS=off -DUTILS=off -DSTATIC_SDL=on -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_C_FLAGS="-fstack-protector -static" -DCMAKE_CXX_FLAGS="-fstack-protector -static -static-libstdc++" -DMINGW=TRUE

# Compile
make -j$(nproc)
