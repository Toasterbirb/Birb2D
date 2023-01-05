#!/bin/bash

# This script will continuously monitor directories
# src, include, utils and tests for changes. If any
# are detected, it will run `make` in the build directory.
#
# If this script is run with the "test" flag, it will also
# run quick tests after done compiling

# You can configure the monitored directories with this
# variable if needed. The paths are relative to the build
# directory. If tests are enabled, the paths will be
# converted to be relative to the tests directory inside
# of the build directory
MONITOR_DIRS="../src ../include ../utils ../tests"
TEST_MONITOR_DIRS="$(echo $MONITOR_DIRS | sed 's/\.\.\//\.\.\/\.\.\//g')"

# Check if we should also test
[ "$1" == "test" ] && TEST=true

# Check if we should test and also use distcc
[ "$1" == "test-distcc" ] && TEST=true && DISTCC=true

BUILD_DIR="$(dirname $0)/../build"

mkdir -pv "$BUILD_DIR"
cd $BUILD_DIR

# Run cmake just in case the build directory is new
# and the build files don't exist yet
if [ "$TEST" == "true" ]
then
	cmake .. -DTESTS=on

	# Enable distcc
	if [ "$DISTCC" == "true" ]
	then
		cmake -DDISTCC=on -DCMAKE_C_COMPILER_LAUNCHER="ccache;distcc" -DCMAKE_CXX_COMPILER_LAUNCHER="ccache;distcc" ..
	fi
else
	cmake ..
fi

# Start monitoring for changes in source code
if [ "$TEST" == "true" ]
then
	cd tests
	if [ "$DISTCC" == "true" ]
	then
		find $TEST_MONITOR_DIRS -print | entr -sc 'time make -j$(distcc -j) && ./test quick'
	else
		find $TEST_MONITOR_DIRS -print | entr -sc 'time make -j$(nproc) && ./test quick'
	fi
else
	find $MONITOR_DIRS -print | entr -sc 'make -j$(nproc)'
fi
