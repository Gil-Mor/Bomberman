#!/bin/bash
set -e
cd "$(dirname "$0")"/..
docker run --rm -it --name bomberman -v `pwd`:`pwd` --workdir `pwd` --network host boost-sfml bash

