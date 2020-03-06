![](https://github.com/Fortuzen/Blockie/workflows/Blockie%20Linux/badge.svg)

# Blockie

C++ clone of a certain game.

## Linux
You need SDL2 dev libraries + SDL2 mixer/ttf/image libraries, cmake, c++ compiler

eg. sudo apt install cmake g++ libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev

### Building

mkdir build

cd build

cmake ..

make

## Windows

### Building

cmake -G "Visual Studio 16 2019" -A Win32 .

Build with Visual Studio (Release Config recommended).
Finally copy assets (from the folder, not the folder) and DLLs (from "libs/<lib>/lib/x86") to the build folder (where is the exe)

Change -G if necessary
