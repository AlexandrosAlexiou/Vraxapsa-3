//  main.cpp
//  VraXaPsa3
//
//  Created by Alexandros Alexiou on 13/11/19.
//  Copyright © 2019 Alexandros Alexiou. All rights reserved.
//
#include <iostream>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "Include/Cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Include/stb_image.h"

using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define maxx 15
#define maxy 15
#define dx 40 // cube pixel width
#define dy 39 // cube pixel height

// Prototypes
void initGL();
void printer(double x, double y, char const * string);
void keyboard(unsigned char c, int x, int y);
void mouseButton(int button, int state, int x, int y);
void display();
void Menu(int choice);
void reshape(GLsizei width, GLsizei height);
void arrowFunctions(int key,int x,int y);
void idle(void);
void  mySolidCube(GLdouble size);
static void drawBox(GLfloat size, GLenum type);
void loadRockTexture(const char* filename);
void loadPaperTexture(const char* filename);
void loadScissorsTexture(const char* filename);
//implementing randomness
void fixRandom();
void fixColours();
//matching
void match3s();
void match2s();

// Global Variables
int num = 0;
int game = 0;
int score_number=0;
char const * score = "SCORE:";
char const * moves = "MOVES:";
char const * game_over="GAME OVER";
int moves_remaining=30;
bool zoom_in = false;
bool zoom_out = false;
bool move_left = false;
bool move_right = false;
bool move_up = false;
bool move_down = false;
GLint i,j,stroke=0,pastx,pasty,nextx,nexty,swap_state=0;

//Default Transformation Variables
double x =-1.0;
double y=-1.15;
double z = -3.5;

//RGB values
GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;

//Data structure of Cubes
Cube array[15][15];

//Texture IDs
unsigned int ID1;
unsigned int ID2;
unsigned int ID3;

//Texture Names
char texture_names[4][8] = { "nothing","Rock","Paper","Scissor" };


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutCreateWindow("VraXaPsa III");
    glutCreateMenu(Menu);
    glutAddMenuEntry("Start Game", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowFunctions);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouseButton);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();
    glutMainLoop();
}
void match2s() {
    int i, j;
    for (i = 0; i < maxx; i++) {
        for (j = 0; j < maxy; j++) {
            //going up
            if (j + 1 <= 14) {
                if (::array[i][j].isPaper() && ::array[i][j+1].isScissor()) {    //paper-scissor =>paper is destroyed
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                    
                }
                else if (::array[i][j].isScissor() && ::array[i ][j + 1].isPaper()){ //scissor-paper =>paper is destroyed
                    ::array[i ][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);
                    ::array[i ][j + 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i ][j + 1].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i ][j + 1].isRock()) { //scissor-rock =>scissor is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isRock() && ::array[i][j + 1].isScissor()) {    //rock-scissor =>scissor is destroyed)
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);
                    ::array[i][j + 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j + 1].setCubeTexture(texture_names[0]);

                
                }
                else if (::array[i][j].isRock() && ::array[i][j + 1].isPaper()) {    //rock-paper =>rock is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isPaper() && ::array[i][j + 1].isRock()) {    //paper -rock =>rock is destroyed)
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);
                    ::array[i][j + 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j + 1].setCubeTexture(texture_names[0]);
                
                }

            }
            //going down
            if (j-1>=0) {
                if (::array[i][j].isPaper() && ::array[i][j - 1].isScissor()) {    //paper-scissor =>paper is destroyed
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i][j - 1].isPaper()) { //scissor-paper =>paper is destroyed
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);
                    ::array[i][j - 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j - 1].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i][j - 1].isRock()) { //scissor-rock =>scissor is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isRock() && ::array[i][j - 1].isScissor()) {    //rock-scissor =>scissor is destroyed)
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);
                    ::array[i][j - 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j - 1].setCubeTexture(texture_names[0]);


                }
                else if (::array[i][j].isRock() && ::array[i][j - 1].isPaper()) {    //rock-paper =>rock is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isPaper() && ::array[i][j - 1].isRock()) {    //paper -rock =>rock is destroyed)
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);
                    ::array[i][j - 1].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j - 1].setCubeTexture(texture_names[0]);

                }
            
            
            }
            //going left
            if (i - 1 >= 0) {
                if (::array[i][j].isPaper() && ::array[i - 1][j].isScissor()) {    //paper-scissor =>paper is destroyed
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i - 1][j].isPaper()) { //scissor-paper =>paper is destroyed
                    ::array[i - 1][j ].setRed(0);
                    ::array[i - 1][j ].setGreen(0);
                    ::array[i - 1][j ].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i - 1][j ].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i - 1][j].isRock()) { //scissor-rock =>scissor is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isRock() && ::array[i - 1][j].isScissor()) {    //rock-scissor =>scissor is destroyed)
                    ::array[i - 1][j ].setRed(0);
                    ::array[i - 1][j ].setGreen(0);
                    ::array[i - 1][j ].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i - 1][j ].setCubeTexture(texture_names[0]);


                }
                else if (::array[i][j].isRock() && ::array[i - 1][j ].isPaper()) {    //rock-paper =>rock is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isPaper() && ::array[i - 1][j ].isRock()) {    //paper -rock =>rock is destroyed)
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j ].setGreen(0);
                    ::array[i - 1][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i - 1][j].setCubeTexture(texture_names[0]);
                }
            }
            //going right
            if (i + 1 <= 14) {
                if (::array[i][j].isPaper() && ::array[i + 1][j].isScissor()) {    //paper-scissor =>paper is destroyed
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i + 1][j].isPaper()) { //scissor-paper =>paper is destroyed
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isScissor() && ::array[i + 1][j].isRock()) { //scissor-rock =>scissor is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isRock() && ::array[i + 1][j].isScissor()) {    //rock-scissor =>scissor is destroyed)
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);


                }
                else if (::array[i][j].isRock() && ::array[i + 1][j].isPaper()) {    //rock-paper =>rock is destroyed)
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i][j].setCubeTexture(texture_names[0]);
                }
                else if (::array[i][j].isPaper() && ::array[i + 1][j].isRock()) {    //paper -rock =>rock is destroyed)
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setBlue(0);
                    score_number = score_number + 2;
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);
                }
            }

            
        }
    
    }

}
void match3s()
{
    int counter = 0;
    int i, j;
    for (i = 0; i < maxx; i++)
    {
        for (j = 0; j < maxy; j++)
        {
            if (j - 1 >= 0 && j + 1 <= 14) {
            //=====================================3 Blues katheta
                if (::array[i][j].isBlue() && ::array[i][j + 1].isBlue() && ::array[i][j - 1].isBlue())
                {
                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);

                    ::array[i][j + 1].setBlue(0);
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);

                    ::array[i][j - 1].setBlue(0);
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);

                    score_number = score_number + 10;
                    printf("SPASIMO KATHETO se BLUE\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i, j - 1, i, j, i, j + 1);
                }
            }
            //===================================== 3 Blues orizontia
            if (i + 1 <= 14 && i - 1 >= 0) {
                if (::array[i][j].isBlue() && ::array[i + 1][j].isBlue() && ::array[i - 1][j].isBlue())
                {
                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);

                    ::array[i + 1][j].setBlue(0);
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);

                    ::array[i - 1][j].setBlue(0);
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j].setGreen(0);

                    score_number = score_number + 10;
                    printf("SPASIMO ORIZONTIO se BLUE\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                }
            }
            //===================================== 3 Reds Katheta
            if(j - 1 >= 0 && j + 1 <= 14){
                if (::array[i][j].isRed() && ::array[i][j + 1].isRed() && ::array[i][j - 1].isRed()) {
                
                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);

                    ::array[i][j + 1].setBlue(0);
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);

                    ::array[i][j - 1].setBlue(0);
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);

                    score_number = score_number + 10;
                    printf("SPASIMO KATHETO se RED\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i, j - 1, i, j, i, j + 1);

                }

            }
            //===================================== 3 Reds orizontia
            if (i + 1 <= 14 && i - 1 >= 0) {
                if (::array[i][j].isRed() && ::array[i + 1][j].isRed() && ::array[i - 1][j].isRed())
                {
                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);

                    ::array[i + 1][j].setBlue(0);
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);

                    ::array[i - 1][j].setBlue(0);
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j].setGreen(0);

                    score_number = score_number + 10;
                    printf("SPASIMO ORIZONTIO se RED\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                }
            }

            //================================== 3 rocks   orizontia
            if (i + 1 <= 14 && i - 1 >= 0) {
                if (::array[i][j].isRock() && ::array[i + 1][j].isRock() && ::array[i - 1][j].isRock())
                {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i + 1][j].setBlue(0);
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);

                    ::array[i - 1][j].setBlue(0);
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j].setGreen(0);
                    ::array[i - 1][j].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO ORIZONTIO se ROCK\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);
                    
                    // ARISTERO APO TA 3
                    // left
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isScissor())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed()){
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i-1][k].isScissor())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed())
                            {
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i-1][k].isScissor())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //MESAIO APO TA 3
                    //up
                    counter=0;
                    row =j;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed()){
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isScissor())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isScissor())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }
                    //DEKSI APO TA 3


                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isScissor())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }

                    //up
                    counter=0;
                    row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed()){
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isScissor())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed())
                            {
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isScissor())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                }
            }

            //================================== 3 rocks   katheta
            if (j - 1 >= 0 && j + 1 <= 14) {
                if (::array[i][j].isRock() && ::array[i ][j + 1].isRock() && ::array[i ][j - 1].isRock()) {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i ][j + 1].setBlue(0);
                    ::array[i ][j + 1].setRed(0);
                    ::array[i ][j + 1].setGreen(0);
                    ::array[i ][j + 1].setCubeTexture(texture_names[0]);

                    ::array[i ][j - 1].setBlue(0);
                    ::array[i ][j - 1].setRed(0);
                    ::array[i ][j - 1].setGreen(0);
                    ::array[i ][j - 1].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO KATHETO se ROCK\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                    //TO PANW APO TA 3
                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isScissor())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // left
                    counter=0;
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isScissor())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isScissor())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }
                    //MESAIO APO TA 3
                    // left
                    counter=0;
                    column =i;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isScissor())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // right
                    counter=0;
                    column =i;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isScissor())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //TERMA KATW APO TA 3
                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isScissor())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // right
                    counter =0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isScissor())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // left
                    counter=0;
                    column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isScissor())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    

                }

            }
            //================================== 3 scissors   orizontia
            if (i + 1 <= 14 && i - 1 >= 0) {
                if (::array[i][j].isScissor() && ::array[i + 1][j].isScissor() && ::array[i - 1][j].isScissor()) {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i + 1][j].setBlue(0);
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);

                    ::array[i - 1][j].setBlue(0);
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j].setGreen(0);
                    ::array[i - 1][j].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO ORIZONTIO se SCISSOR\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);
                    
                    // ARISTERO APO TA 3
                    // left
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isPaper())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed()){
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i-1][k].isPaper())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed())
                            {
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i-1][k].isPaper())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //MESAIO APO TA 3
                    //up
                    counter=0;
                    row =j;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed()){
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isPaper())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isPaper())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }
                    //DEKSI APO TA 3


                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isPaper())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }

                    //up
                    counter=0;
                    row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed()){
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isPaper())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed())
                            {
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isPaper())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }
                    


                }

            }
            //================================== 3 scissors   katheta
            if (j - 1 >= 0 && j + 1 <= 14) {
                if (::array[i][j].isScissor() && ::array[i][j + 1].isScissor() && ::array[i][j - 1].isScissor()) {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i][j + 1].setBlue(0);
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);
                    ::array[i][j + 1].setCubeTexture(texture_names[0]);

                    ::array[i][j - 1].setBlue(0);
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);
                    ::array[i][j - 1].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO KATHETO se SCISSOR\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                    //TO PANW APO TA 3
                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                       
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isPaper())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // left
                    counter=0;
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isPaper())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isPaper())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }
                    //MESAIO APO TA 3
                    // left
                    counter=0;
                    column =i;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isPaper())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // right
                    counter=0;
                    column =i;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isPaper())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //TERMA KATW APO TA 3
                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isPaper())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // right
                    counter =0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isPaper())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // left
                    counter=0;
                    column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isPaper())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                }

            }
            //================================== 3 paper   orizontia
            if (i + 1 <= 14 && i - 1 >= 0) {
                if (::array[i][j].isPaper() && ::array[i + 1][j].isPaper() && ::array[i - 1][j].isPaper()) {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i + 1][j].setBlue(0);
                    ::array[i + 1][j].setRed(0);
                    ::array[i + 1][j].setGreen(0);
                    ::array[i + 1][j].setCubeTexture(texture_names[0]);

                    ::array[i - 1][j].setBlue(0);
                    ::array[i - 1][j].setRed(0);
                    ::array[i - 1][j].setGreen(0);
                    ::array[i - 1][j].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO ORIZONTIO se PAPER\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                    // ARISTERO APO TA 3
                    // left
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isRock())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed()){
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number++;
                            }
                        }
                        
                        if (::array[i-1][k].isRock())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i-1][k].isBlue() || ::array[i-1][k].isRed())
                            {
                                ::array[i-1][k].setBlue(0);
                                ::array[i-1][k].setRed(0);
                                ::array[i-1][k].setGreen(0);
                                ::array[i-1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i-1][k].isRock())
                        {
                            ::array[i-1][k].setBlue(0);
                            ::array[i-1][k].setRed(0);
                            ::array[i-1][k].setGreen(0);
                            ::array[i-1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //MESAIO APO TA 3
                    //up
                    counter=0;
                    row =j;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed()){
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isRock())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isRock())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }
                    //DEKSI APO TA 3


                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isRock())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }

                    //up
                    counter=0;
                    row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed()){
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isRock())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i+1][k].isBlue() || ::array[i+1][k].isRed())
                            {
                                ::array[i+1][k].setBlue(0);
                                ::array[i+1][k].setRed(0);
                                ::array[i+1][k].setGreen(0);
                                ::array[i+1][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i+1][k].isRock())
                        {
                            ::array[i+1][k].setBlue(0);
                            ::array[i+1][k].setRed(0);
                            ::array[i+1][k].setGreen(0);
                            ::array[i+1][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }


                }

            }
            //================================== 3 paper   katheta
            if (j - 1 >= 0 && j + 1 <= 14) {
                if (::array[i][j].isPaper() && ::array[i][j + 1].isPaper() && ::array[i][j - 1].isPaper()) {

                    ::array[i][j].setBlue(0);
                    ::array[i][j].setRed(0);
                    ::array[i][j].setGreen(0);
                    ::array[i][j].setCubeTexture(texture_names[0]);

                    ::array[i][j + 1].setBlue(0);
                    ::array[i][j + 1].setRed(0);
                    ::array[i][j + 1].setGreen(0);
                    ::array[i][j + 1].setCubeTexture(texture_names[0]);

                    ::array[i][j - 1].setBlue(0);
                    ::array[i][j - 1].setRed(0);
                    ::array[i][j - 1].setGreen(0);
                    ::array[i][j - 1].setCubeTexture(texture_names[0]);

                    score_number = score_number + 10;
                    printf("SPASIMO KATHETO se PAPER\n");
                    printf("ESPASAN TA i: %d j: %d i: %d j: %d i: %d j:%d\n", i - 1, j, i, j, i + 1, j);

                    //TO PANW APO TA 3
                    //up
                    counter=0;
                    int row =j+1;
                    for (int k = row; k <=14; k++)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isRock())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // left
                    counter=0;
                    int column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isRock())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //right
                    counter=0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j+1].isBlue() || ::array[k][j+1].isRed()){
                                ::array[k][j+1].setBlue(0);
                                ::array[k][j+1].setRed(0);
                                ::array[k][j+1].setGreen(0);
                                ::array[k][j+1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j+1].isRock())
                        {
                            ::array[k][j+1].setBlue(0);
                            ::array[k][j+1].setRed(0);
                            ::array[k][j+1].setGreen(0);
                            ::array[k][j+1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                    }
                    //MESAIO APO TA 3
                    // left
                    counter=0;
                    column =i;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isRock())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // right
                    counter=0;
                    column =i;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j].isBlue() || ::array[k][j].isRed()){
                                ::array[k][j].setBlue(0);
                                ::array[k][j].setRed(0);
                                ::array[k][j].setGreen(0);
                                ::array[k][j].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j].isRock())
                        {
                            ::array[k][j].setBlue(0);
                            ::array[k][j].setRed(0);
                            ::array[k][j].setGreen(0);
                            ::array[k][j].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    //TERMA KATW APO TA 3
                    //down
                    counter=0;
                    row =j-1;
                    for (int k = row; k >=0; k--)
                    {
                        if (counter == 3) {
                            break;
                        }
                        
                        if(counter<2){
                            if (::array[i][k].isBlue() || ::array[i][k].isRed())
                            {
                                ::array[i][k].setBlue(0);
                                ::array[i][k].setRed(0);
                                ::array[i][k].setGreen(0);
                                ::array[i][k].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        }
                        
                        if (::array[i][k].isRock())
                        {
                            ::array[i][k].setBlue(0);
                            ::array[i][k].setRed(0);
                            ::array[i][k].setGreen(0);
                            ::array[i][k].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }
                        counter++;
                        
                    }

                    // right
                    counter =0;
                    column =i+1;
                    for (int k = column; k <=14; k++)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isRock())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }

                    // left
                    counter=0;
                    column =i-1;
                    for (int k = column; k >=0; k--)
                    {
                        
                        if (counter == 3) {
                            break;
                        }
                        if(counter<2){
                            if (::array[k][j-1].isBlue() || ::array[k][j-1].isRed()){
                                ::array[k][j-1].setBlue(0);
                                ::array[k][j-1].setRed(0);
                                ::array[k][j-1].setGreen(0);
                                ::array[k][j-1].setCubeTexture(texture_names[0]);
                                score_number = score_number + 2;
                            }else{
                                score_number--;
                            }
                        
                        }
                        
                        if ( ::array[k][j-1].isRock())
                        {
                            ::array[k][j-1].setBlue(0);
                            ::array[k][j-1].setRed(0);
                            ::array[k][j-1].setGreen(0);
                            ::array[k][j-1].setCubeTexture(texture_names[0]);
                            score_number = score_number + 3;
                        }

                        counter++;
                        
                    }
                    
                }

            }
            
        }
    }
    
}
            
void fixColours() {

    for (i = 0; i < maxx-2 ; i++)
    {
        for (j = 0; j < maxy-2 ; j++)
        {

            //==============================================================================================================
            //fix horizontal blues
            if (::array[i][j].isBlue() && ::array[i][j + 1].isBlue() && ::array[i][j + 2].isBlue()) {

                ::array[i][j + 1].setBlue(0);
                ::array[i][j + 1].setRed(255);    //make it red
                //::array[i][j + 1].setCubeTexture(texture_names[0]);
            }
            //fix vertical blues
            if (::array[i][j].isBlue() && ::array[i + 1][j].isBlue() && ::array[i + 2][j].isBlue()) {

                ::array[i + 1][j].setBlue(0);
                ::array[i + 1][j].setRed(255);        //make it red
                //::array[i + 1][j].setCubeTexture(texture_names[0]);

            }

            //==============================================================================================================
            //fix horizontal reds
            if (::array[i][j].isRed() && ::array[i][j + 1].isRed() && ::array[i][j + 2].isRed()) {

                ::array[i][j + 1].setRed(0);
                ::array[i][j + 1].setBlue(255);                //make it blue
                //::array[i][j + 1].setCubeTexture(texture_names[0]);
            }
            //fix vertical reds
            if (::array[i][j].isRed() && ::array[i + 1][j].isRed() && ::array[i + 2][j].isRed()) {
                ::array[i + 1][j].setRed(0);
                ::array[i + 1][j].setBlue(255);            //make it blue
                //::array[i + 1][j].setCubeTexture(texture_names[0]);
            }
        }
    }
}
//if tiles are same i fix
void fixRandom() {
    
    for (i = 0; i < maxx - 1; i++)
    {
        for (j = 0; j < maxy - 1; j++)
        {
            //==================================================================================================================
            //fix 2 horizontal items
            if (::array[i][j].isItem() && ::array[i][j + 1].isItem()) {

                ::array[i][j + 1].setCubeTexture(texture_names[0]);    //make it blue
                ::array[i][j + 1].setRed(0);
                ::array[i][j + 1].setGreen(0);

            }
            //fix 2 vertical items
            if (::array[i][j].isItem() && ::array[i + 1][j].isItem()) {
                ::array[i + 1][j].setCubeTexture(texture_names[0]);    //make it red
                ::array[i + 1][j].setBlue(0);
                ::array[i + 1][j].setGreen(0);

            }
            

        }
        
    }
    

}
void initGL()
{
    
    loadRockTexture("textures/stone.bmp");
    loadPaperTexture("textures/paper.png");
    loadScissorsTexture("textures/scissors.bmp");
    glEnable(GL_DEPTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    //glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glTranslatef(-6, -6, -15.5);
    
    int i,j,rng;
    srand( static_cast<unsigned int>(time(0)));
    for(i=0; i < maxx; i++)
    {
        for(j=0; j < maxy; j++)
        {
            rng = (rand()%100);//pick a random number in range [1,100]
            
            
            if(rng<15)        //blue tile,no texture
            {
                
                ::array[i][j].setBlue(255);
                ::array[i][j].setCubeTexture(texture_names[0]);
            }
            else if (rng>15 && rng<30)    //red tile ,no texture
            {
                ::array[i][j].setRed(255);
                ::array[i][j].setCubeTexture(texture_names[0]);
            }
            else if (rng > 30 && rng < 55)    //scissor
            {
                ::array[i][j].setCubeTexture(texture_names[3]);
                ::array[i][j].setRed(255);
                ::array[i][j].setGreen(255);
                ::array[i][j].setBlue(255);
            }
            else if(rng >55 && rng <80)
            {
                ::array[i][j].setCubeTexture(texture_names[1]);    //rock
                ::array[i][j].setRed(255);
                ::array[i][j].setGreen(255);
                ::array[i][j].setBlue(255);
            }
            else
            {
                ::array[i][j].setCubeTexture(texture_names[2]);    //paper
                ::array[i][j].setRed(255);
                ::array[i][j].setGreen(255);
                ::array[i][j].setBlue(255);
            }
        }
    }
    fixColours();
    fixRandom();
    fixColours();
    
}

void arrowFunctions(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        cout << "Camera up\n";
        move_up = true;
        
    }
    if (key == GLUT_KEY_DOWN)
    {
        cout << "Camera down\n";
        move_down = true;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        cout << "Camera right\n";
        move_right = true;

    }
    if (key == GLUT_KEY_LEFT)
    {
        cout << "Camera left\n";
        move_left = true;
    }

}


void keyboard(unsigned char c, int x, int y)
{
    if (c == 27)
    {
        printf("esc");
        exit(0);
    }
    if (c == 61)
    {
        //we need to zoom in,with '=' no shift required
        zoom_in = true;
        printf("ZOOM IN\n");
    }
    if (c == 45)
    {
        //we need to zoom out with '-'
        zoom_out = true;
        printf("ZOOM OUT\n");
    }
    
}

void mouseButton(int button, int state, int x, int y)
{
    if(y<20 || x>600 || y>600 || x<0){ //abort we have a margin of 20 pixels for the score and moves header on top of the screen.
        return;
    }
    printf("x=%d,y=%d\n",x,y);
    y=600-y;
    if((stroke == 0) && (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        stroke=1;
        pastx=x;
        pasty=y;
        //printf("pastx=%d,%d\n",pastx/dx,pasty/dy);
    }
    if((stroke == 1) && (button == GLUT_LEFT_BUTTON) && (state== GLUT_UP))
    {
        stroke=0;
        nextx=x;
        nexty=y;
        //printf("nextx=%d,%d\n",nextx/dx,nexty/dy);
        if( ( (abs((pastx/dx)-(nextx/dx)) == 1) && ((pasty/dy) == (nexty/dy)) ) || ( (abs((pasty/dy)-(nexty/dy)) == 1) && ((pastx/dx) == (nextx/dx)) ) )
            swap_state=1;
        
    }

}


void idle(void)
{
    int tempRed;
    int tempGreen;
    int tempBlue;
    char *tempTexture;
    if(game==0){ // interact with cubes only if the game is on
        return;
    }
    if (swap_state)
    {
        swap_state = 0;
        tempRed = ::array[pastx / dx][pasty / dy].getRed();
        tempGreen = ::array[pastx / dx][pasty / dy].getGreen();
        tempBlue = ::array[pastx / dx][pasty / dy].getBlue();
        
        tempTexture=::array[pastx / dx][pasty / dy].getCubeTexture();
        ::array[pastx / dx][pasty / dy].setRed(::array[nextx / dx][nexty / dy].getRed());
        ::array[pastx / dx][pasty / dy].setGreen(::array[nextx / dx][nexty / dy].getGreen());
        ::array[pastx / dx][pasty / dy].setBlue(::array[nextx / dx][nexty / dy].getBlue());
        ::array[pastx / dx][pasty / dy].setCubeTexture( ::array[nextx / dx][nexty / dy].getCubeTexture());
    
        ::array[nextx / dx][nexty / dy].setRed(tempRed);
        ::array[nextx / dx][nexty / dy].setGreen(tempGreen);
        ::array[nextx / dx][nexty / dy].setBlue(tempBlue);
        ::array[nextx / dx][nexty / dy].setCubeTexture(tempTexture);
        //Checks
        int pastX=pastx/dx;
        int pastY=pasty/dy;
        int nextX=nextx/dx;
        int nextY=nexty/dy;
        printf("SWAPPED:\n");
        printf("pastX=%d pastY=%d <-------->  nextX=%d nextY=%d\n",pastX,pastY,nextX,nextY);
        moves_remaining--;
    }
    match3s();
    match2s();
    glutPostRedisplay();
}

void printer(double x, double y,char const * string)
{
    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);
    //get the length of the string to display
    int len = (int)strlen(string);
    // loop to display character by character
    glColor3ub(255, 0, 200);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

void loadRockTexture(const char* filename) {
    int width, height,nrChannels;
    unsigned char * data =stbi_load(filename, &width, &height, &nrChannels, 0);
    
    glGenTextures(1,&ID1);
    glBindTexture(GL_TEXTURE_2D,ID1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    //can play with those
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);//GL{REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//ALSO
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
}

void loadPaperTexture(const char* filename) {
    int width, height,nrChannels;
    unsigned char * data =stbi_load(filename, &width, &height, &nrChannels, 0);
    
    glGenTextures(1,&ID2);
    glBindTexture(GL_TEXTURE_2D,ID2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    //can play with those
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);//GLREPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//ALSO
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
}

void loadScissorsTexture(const char* filename) {
    int width, height,nrChannels;
    unsigned char * data =stbi_load(filename, &width, &height, &nrChannels, 0);
    
    glGenTextures(1,&ID3);
    glBindTexture(GL_TEXTURE_2D,ID3);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    //can play with those
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);//GLREPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//ALSO
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
}

static void drawBox(GLfloat size, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  glEnable(GL_TEXTURE_2D);
  for (i = 5; i >= 0; i--) {
      glBegin(type);
      glNormal3fv(&n[i][0]);
      glTexCoord2f(1.0,1.0);  glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(0.0, 1.0); glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(0.0, 0.0); glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2d(1.0, 0.0); glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}

void  mySolidCube(GLdouble size)
{
  drawBox(size, GL_QUADS);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //katharizei k dinei to background color
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    
    if(moves_remaining==0) //Game Over
    {
        game = 0;
        //Print game over
        glPushMatrix();
        glColor3ub(255, 0, 255);
        glScalef(1, 1 ,1);
        printer(5.5, 6, game_over);
        glPopMatrix();
        
        //Print score
        glPushMatrix();
        glColor3ub(255, 0, 255);
        glScalef(1, 1 ,1);
        printer(5.5, 5, score);
        glPopMatrix();
        
        //Print score number
        glPushMatrix();
        glColor3ub(255, 0, 255);
        string score_number_string=to_string(score_number);
        char const *kchar = score_number_string.c_str();
        printer(8, 5, kchar);
        glPopMatrix();
        game=-1;
    }
    
    if (game == 0)
    {
        for (int i = 0; i < maxx; i++)
        {
            for (int j = 0; j < maxy; j++)
            {
                glPushMatrix();
                glColor3ub(207, 185, 151);
                glTranslatef(x + i, y + j, z);
                glutSolidCube(0.7);
                glPopMatrix();
            }
        }
    }
   
    if(game==1)
    {
        
        //Print SCORE:
        glPushMatrix();
        glColor3ub(255, 0, 255);
        printer(8, 12, score);
        glPopMatrix();
        
        //Print score number
        glPushMatrix();
        glColor3ub(255, 0, 255);
        string score_number_string=to_string(score_number);
        char const *kchar = score_number_string.c_str();
        printer(10, 12, kchar);
        glPopMatrix();
        
        //Print MOVES:
        glPushMatrix();
        glColor3ub(255, 0, 255);
        printer(0, 12, moves);
        glPopMatrix();
        
        //Print remaining moves
        glPushMatrix();
        glColor3ub(255, 0, 255);
        string moves_remaining_string = to_string(moves_remaining);
        char const *pchar = moves_remaining_string.c_str();
        printer(2, 12, pchar);
        glPopMatrix();
        
        
        for (int i = 0; i < maxx; i++)
        {
            for (int j = 0; j < maxy; j++)
            {
                if (strcmp(texture_names[1], ::array[i][j].getCubeTexture())==0){
                    
                    glBindTexture(GL_TEXTURE_2D,ID1);
                }
                if (strcmp(texture_names[2], ::array[i][j].getCubeTexture())==0) {
                    
                    glBindTexture(GL_TEXTURE_2D, ID2);
                }
                if (strcmp(texture_names[3], ::array[i][j].getCubeTexture()) == 0) {
                    
                    glBindTexture(GL_TEXTURE_2D, ID3);
                }
                if (strcmp(texture_names[0], ::array[i][j].getCubeTexture()) == 0) {
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                glPushMatrix();
                glColor3ub(::array[i][j].getRed(),::array[i][j].getGreen(),::array[i][j].getBlue());
                glTranslatef(x + i, y + j, z);
                //printf(" SUNTETAGMENES KUVOU i=%d j=%d\n",i,j);
                //printf(" x=%f y=%f z=%f",::array[i][j].getX(),::array[i][j].getY(),::array[i][j].getZ());
                mySolidCube(0.7);
                glPopMatrix();
            }
        }
        if (zoom_in)
         {
            gluLookAt(0, 0, -10.5, 0, 0, -15.5,0, 1, -15.5);
            zoom_in = false;
        }
        if (zoom_out)
        {
            
            gluLookAt(0, 0, 10.5, 0, 0, -15.5, 0, 1, -15.5);
            
            zoom_out = false;
        }
        if (move_left)
        {
            gluLookAt(-1, 0, 0,-1, 0, -15.5, 0, 1, -15.5);

            move_left = false;
            
        }
        if (move_right)
        {
            gluLookAt(1, 0, 0, 1, 0, -15.5, 0, 1, -15.5);
            move_right = false;

        }
        if (move_up)
        {
            gluLookAt(0, 1, 0, 0, 1, -15.5, 0, 1, -15.5);
            move_up = false;
        }
        if (move_down)
        {
            gluLookAt(0, -1, 0, 0, -1, -15.5, 0, 1, -15.5);
            move_down = false;
        }
        
    }
    glFlush();
    glutSwapBuffers();
}



void Menu(int choice)
{
    if (choice == 1)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        game = 1;
        
    }
    if (choice == 2)
    {
        exit(0);
    }
    
    glutPostRedisplay();    //for menu option to take immediate effect
}

/* Handler for window re-size event.
Called back when the window first appears and whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{
    // GLsizei for non-negative integer // Compute aspect ratio of the new window
    if (height == 0) height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height; // Set the viewport to cover the new window
    glViewport(0, 0, width, height); // Set the aspect ratio of the clipping volume
    glutReshapeWindow(600, 600);
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
