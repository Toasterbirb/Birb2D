#!/bin/sh

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

BUILD_DIR="$(dirname $0)/../build"

mkdir -pv "$BUILD_DIR"
cd $BUILD_DIR

# Run cmake just in case the build directory is new
# and the build files don't exist yet
if [ "$TEST" == "true" ]
then
	cmake .. -DTESTS=on
else
	cmake ..
fi

# Start monitoring for changes in source code
if [ "$TEST" == "true" ]
then
	cd tests
	find $TEST_MONITOR_DIRS -print | entr -sc 'make -j$(nproc) && ./test quick'
else
	find $MONITOR_DIRS -print | entr -sc 'make -j$(nproc)'
fi
