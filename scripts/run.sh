#!/bin/bash

if [ "$1" = "release" ]
then
    ./build/release/cellular-automaton
else
    ./build/debug/cellular-automaton
fi