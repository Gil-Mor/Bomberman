FROM ubuntu:18.04

# set up dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    pkg-config \
    cmake \
    libboost-all-dev \
    libsfml-dev

# Auxiliary tools - code formatting.
# Use if you want to commit new code.
# Usage:
# After running `cmake ..` from 'build' directory run:
# make format
RUN apt-get update && apt-get install -y \
    clang-format-6.0

    

