#!/usr/bin/env bash
clear
if [ $1 = "gcc" ]; then
    echo "Compiler: gcc"
    export CXX=/usr/bin/g++
elif [ $1 = "clang" ]; then
    echo "Compiler: clang"
    export CXX=/usr/bin/clang++
fi
mkdir _build
cd _build
cmake ..
make