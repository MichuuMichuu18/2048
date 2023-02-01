# 2048
2048 game written in C using freeglut library

![Game screenshot](screenshot.png)

# Build instructions

You need to install Git, freeglut development files and GNU GCC compiler:

Debian/Ubuntu:
````
sudo apt install git gcc freeglut3-dev
````

Fedora:
````
sudo dnf install git gcc freeglut-devel
````

Arch:
````
sudo pacman -S git gcc freeglut
````

Then clone repository and compile source code:

````
git clone https://github.com/MichuuMichuu18/2048.git
cd 2048
gcc 2048.c -o 2048 -lGL -lGLU -lglut -lm
````
