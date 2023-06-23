#! /bin/sh

if [[ -d "build" ]]
then
    cd build
else
    mkdir build
    cd build
fi

cmake -D CMAKE_BUILD_TYPE=Debug ..
make gameoflife
