## Linux
Not implemented yet
sudo apt install cmake libsdl2-dev g++

## Windows

cmake -G "Visual Studio 16 2019" -A Win32 .

Build with Visual Studio (Release Config recommended).
Finally copy assets and DLLs (from "libs/<lib>/lib/x86") to the build folder.