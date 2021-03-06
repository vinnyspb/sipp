#!/bin/bash

wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
echo "deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.8 main" | sudo tee -a /etc/apt/sources.list >/dev/null
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get -qq --assume-yes install clang-3.8 lldb-3.8
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.8 100

sudo apt-get install -qq --assume-yes g++-5 gcc-5
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 90
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 90

CMAKE_VERSION=3.3.2
CMAKE_VERSION_DIR=v3.3

CMAKE_OS=Linux-x86_64
CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
CMAKE_DIR=$(pwd)/cmake-$CMAKE_VERSION

wget --quiet $CMAKE_URL
mkdir -p $CMAKE_DIR
tar --strip-components=1 -xzf $CMAKE_TAR -C $CMAKE_DIR
export PATH=$CMAKE_DIR/bin:$PATH

