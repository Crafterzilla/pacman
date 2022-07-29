#!/bin/bash

sudo apt update && sudo apt upgrade

#Install some other important tools
sudo apt install git-all
sudo apt install build-Essentials
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt install cmake


#install raylib
cd ~/Documents

git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
sudo ldconfig

#Install, compile, and run game
cd ~/Documents
git clone https://github.com/Crafterzilla/pacman.git pacman
cd pacman/

g++ -O -o pacman main.cpp -s ./src/*.cpp -Wall -lraylib -lm -lpthread -ldl -lrt -lX11
echo Complied
mv pacman ./build/pacman
./build/pacman
