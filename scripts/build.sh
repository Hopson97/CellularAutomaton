#!/bin/bash

target_release() {
    cd release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    make
    echo "Built target in build/release/"
    cd ../..
}

target_debug() {
    cd debug 
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    make
    echo "Built target in build/debug/"
    cd ../..
}

# Create folder for distribution
if [ "$1" = "release" ]
then
    if [ -d "$cellular-automaton" ]
    then
        rm -rf -d cellular-automaton
    fi

    mkdir -p cellular-automaton
fi

# Creates the folder for the buildaries
mkdir -p cellular-automaton 
mkdir -p cellular-automaton/assets
mkdir -p build
mkdir -p build/release
mkdir -p build/debug
cd build

# Builds target
if [ "$1" = "release" ]
then
    target_release
    cp build/release/cellular-automaton cellular-automaton/cellular-automaton
else
    target_debug
fi

cp -R assets cellular-automaton/
