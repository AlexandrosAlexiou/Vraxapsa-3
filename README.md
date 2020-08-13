# Vraxapsa-3
A mini game built using the OpenGL/GLUT API.


## How to play.
It is a game like Rock-Paper-Scissors and Candy Crush combined. 

**Rules are simple:**

1. Make 3s of the same cube type. 
2. 3s of paper or rock or scissors explode.
3. To swap cubes hold the cube you want to move with the left click and release the click on the cube you want to swap it with. (Kinda like you play on a touch screen with a finger swipe.)

## Run on mac
1. The repository is an Xcode project.
2. OpenGL and GLUT are preinstalled in Mac OS.
3. Add https://github.com/nothings/stb/blob/master/stb_image.h into the Include folder of the repository.
4. Open the project with Xcode and build it.

## Run on linux
1. You need to have OpenGl and Glut installed.
2. Add https://github.com/nothings/stb/blob/master/stb_image.h into the Include folder of the repository.
3. Delete lines 12 and 13, add **#include <GL/glut.h>** and compile with the Makefile.
   
 
Game Board:

![Game Board](https://github.com/AlexandrosAlexiou/Vraxapsa-3/blob/master/game_board.png)
