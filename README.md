# 2048
2048 game written in C using freeglut library

![Game screenshot](screenshot.png)

# Build instructions
You need to install freeglut headers and build tools:

Debian/Ubuntu:
````
sudo apt install gcc freeglut3-dev
````

Fedora:
````
sudo dnf install gcc freeglut-devel
````

Arch:
````
sudo pacman -S gcc freeglut
````

After installing run this command in cloned repository:

````
gcc 2048.c -o 2048 -lGL -lGLU -lglut -lm
````