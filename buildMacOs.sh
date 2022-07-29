#!/bin/bash

set -e

cd
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew update
brew upgrade
brew install raylib
brew install pkgconfig
brew install git
brew install gcc

#Find gnu g++ compiler
cd /usr/local/bin
touch compilerType.txt
ls g++* >> compilerType.txt
COMPILER = $(cat compilerType.txt | tail -1)
rm compilerType.txt

#Install My game through my gihub
cd ~/Documents
git clone https://github.com/Crafterzilla/pacman.git pacman
cd pacman

#Run and Compile game
$COMPILER -O main.cpp ./src/*.cpp  `pkg-config --libs --cflags raylib` -o pacman
./build/pacman

