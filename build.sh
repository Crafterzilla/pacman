set -e

g++ -S main.cpp ./src/*.cpp
mv *.s ./assembly
g++ -O -o pacman main.cpp -s ./src/*.cpp -Wall -lraylib -lm -lpthread -ldl -lrt -lX11
echo Complied
mv pacman ./build/pacman
./build/pacman