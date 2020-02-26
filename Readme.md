## Linux
You need SDL2 dev libraries including mixer/ttf/image

sudo apt install cmake libsdl2-dev g++

mkdir build
cd build
cmake ..
make

## Windows

cmake -G "Visual Studio 16 2019" -A Win32 .

Build with Visual Studio (Release Config recommended).
Finally copy assets (from the Assets, not the folder) and DLLs (from "libs/<lib>/lib/x86") to the build folder (where is the exe)

Change -G if necessary
