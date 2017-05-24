#!/bin/sh

# Delete build dir
echo Deleting build directory
cd ..
rm -rf build/

# Create build dir
echo Creating the build directory
mkdir build

# Define compilation
echo Generating build files
cd build
CXX='../helpers/cc_args.py g++' cmake ..
