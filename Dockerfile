FROM ubuntu:18.04

# set up dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    pkg-config \
    cmake \
    libboost-all-dev \
    libsfml-dev
    

