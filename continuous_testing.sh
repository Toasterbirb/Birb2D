#!/bin/sh
mkdir -p build
cd build
find ../src/ -print | entr -sc 'cd .. ; make -j4 && cd build ; ./birb2d_test'
