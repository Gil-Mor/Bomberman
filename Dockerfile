FROM ubuntu:18.04

# set up code dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    pkg-config \
    cmake \
    libboost-all-dev \
    libsfml-dev

# Auxiliary tools - code formatting and Static Code analysis.
# Use if you want to commit new code.
# Usage:
# After running `cmake ..` from 'build' directory run:
# make format
# make clang-tidy
# make junit
RUN apt-get update && apt-get install -y \
    clang-format-6.0 \
    clang-tidy \
    python-pip \
    && \
    pip install junit2html



