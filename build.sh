set -e

g++ -S main.cpp ./src/*.cpp
mv *.s ./assembly
g++ -g3 -o pacman main.cpp ./src/*.cpp -Wall -lraylib -lm -lpthread -ldl -lrt -lX11
echo Complied
mv pacman ./build/pacman
./build/pacman