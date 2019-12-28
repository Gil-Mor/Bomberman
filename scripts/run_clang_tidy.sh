#!/bin/bash
set -e
cd "$(dirname "$0")"/..
docker exec -it bomberman sh -c 'cd build && cmake -DRUN_CLANG_TIDY=ON .. && make clean all -j`nproc` && make clang-tidy && make junit'

