# 2048
2048 game written in C using freeglut library

![Game screenshot](screenshot.png)

# Build instructions

You need to install Git, freeglut development files, GNU GCC compiler and CMake:

Debian/Ubuntu:
````
sudo apt install git freeglut3-dev gcc cmake
````

Fedora:
````
sudo dnf install git freeglut-devel gcc cmake
````

Arch:
````
sudo pacman -S git freeglut gcc cmake
````

Then clone repository and compile source code:

````
git clone https://github.com/MichuuMichuu18/2048.git
mkdir 2048/build && cd 2048/build
cmake ..
make
````
