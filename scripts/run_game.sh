#!/bin/bash

set -e

cd "$(dirname "$0")"/..
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PWD}/build
cd build
./bomberman
