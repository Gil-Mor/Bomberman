#!/bin/bash
set -e
cd "$(dirname "$0")"/..
docker exec -it bomberman sh -c 'cd build && cmake .. && make -j16'

