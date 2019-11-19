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

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define maxx 15
#define maxy 15
#define dx 40
#define dy 40

using namespace std;
// Prototypes
void initGL();
void printer(double x, double y, char* string);
void keyboard(unsigned char c, int x, int y);
void mouseButton(int button, int state, int x, int y);
void display();
void Menu(int choice);
void reshape(GLsizei width, GLsizei height);
void arrowFunctions(int key,int x,int y);
void idle(void);

// Global Variables
int num = 0;
bool game = 0;
char score[7] = "Score:";
char moves[7] = "Moves:";
char game_over[10]="GAME OVER";
int moves_remaining=30;
bool zoom_in = false;
bool zoom_out = false;
bool move_left = false;
bool move_right = false;
bool move_up = false;
bool move_down = false;
GLint i,j,stroke=0,pastx,pasty,nextx,nexty,swapthetwo=0;


//Default Transformation Variables
double x =-1.0;
double y=-0.85;
double z = -3.5;
GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;

//Data structure of Cubes
Cube cubes_render_board[15][15];

int main(int argc, char** argv) {
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
    //glutSpecialFunc(arrowFunctions);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouseButton);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();
    glutMainLoop();
}



void initGL() {
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
    for(i=0; i < maxx; i++){
        
        for(j=0; j < maxy; j++){
            
            rng = (rand()%5)+1;
    
            if(rng==1){
                ::cubes_render_board[i][j].setBlue(255);
                
            }else if (rng==2){
                ::cubes_render_board[i][j].setRed(255);
                
            }else if (rng==3){
                ::cubes_render_board[i][j].setCubeTexture("Psalidi");
                ::cubes_render_board[i][j].setGreen(255);
                
            }else if(rng==4){
                ::cubes_render_board[i][j].setCubeTexture("Vraxos");
                ::cubes_render_board[i][j].setRed(255);
                ::cubes_render_board[i][j].setGreen(255);
                ::cubes_render_board[i][j].setBlue(255);
                
            }else{
                ::cubes_render_board[i][j].setCubeTexture("Xarti");
                ::cubes_render_board[i][j].setRed(255);
                ::cubes_render_board[i][j].setBlue(255);
            }
        }
    }
}

void arrowFunctions(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cout << "Camera Panw\n";
        move_up = true;
        
    }
    if (key == GLUT_KEY_DOWN) {
        cout << "Camera Katw\n";
        move_down = true;
    }
    if (key == GLUT_KEY_RIGHT) {
        cout << "Camera dexia\n";
        move_right = true;

    }
    if (key == GLUT_KEY_LEFT) {
        cout << "Camera Aristera\n";
        move_left = true;
    }

}


void keyboard(unsigned char c, int x, int y) {
    if (c == 27) {
        printf("esc");
        exit(0);
    }
    if (c == 61) {
        //we need to zoom in,with '=' no shift required
        zoom_in = true;
        printf("ZOOM IN\n");
    }
    if (c == 45) {
        //we need to zoom out with '-'
        zoom_out = true;
        printf("ZOOM OUT\n");
    }
}

void mouseButton(int button, int state, int x, int y) {
   // printf("x=%d,y=%d\n",x,y);
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
        if((abs((pastx/dx)-(nextx/dx)) == 1) && ((pasty/dy) == (nexty/dy)))
            swapthetwo=1;
        if((abs((pasty/dy)-(nexty/dy)) == 1) && ((pastx/dx) == (nextx/dx)))
            swapthetwo=1;
    }

}


void idle(void){
    int tempRed;
    int tempGreen;
    int tempBlue;
    
    if(swapthetwo)
    {
        swapthetwo=0;
        tempRed=::cubes_render_board[pastx/dx][pasty/dy].getRed();
        tempGreen=::cubes_render_board[pastx/dx][pasty/dy].getGreen();
        tempBlue=::cubes_render_board[pastx/dx][pasty/dy].getBlue();
        
        ::cubes_render_board[pastx/dx][pasty/dy].setRed(::cubes_render_board[nextx/dx][nexty/dy].getRed());
        ::cubes_render_board[pastx/dx][pasty/dy].setGreen(::cubes_render_board[nextx/dx][nexty/dy].getGreen());
        ::cubes_render_board[pastx/dx][pasty/dy].setBlue(::cubes_render_board[nextx/dx][nexty/dy].getBlue());
        
        ::cubes_render_board[nextx/dx][nexty/dy].setRed(tempRed);
        ::cubes_render_board[nextx/dx][nexty/dy].setGreen(tempGreen);
        ::cubes_render_board[nextx/dx][nexty/dy].setBlue(tempBlue);
        
        //printf("swapped");
        int pastX=pastx/dx;
        int pastY=pasty/dy;
        
        int nextX=nextx/dx;
        int nextY=nexty/dy;
        printf("SWAPPED:\n");
        printf("pastX=%d pastY=%d -------->  nextX=%d nextY=%d\n",pastX,pastY,nextX,nextY);
    }
    glutPostRedisplay();
}

void printer(double x, double y, char* string) {
    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);
    //get the length of the string to display
    int len = (int)strlen(string);
    // loop to display character by character
    glColor3ub(255, 0, 200);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //katharizei k dinei to background color
    //glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    if (game == 0) {
        for (int i = 0; i < maxx; i++) {
            for (int j = 0; j < maxy; j++) {
                glPushMatrix();
                glColor3ub(207, 185, 151);
                glTranslatef(x + i, y + j, z);
                ::cubes_render_board[i][j].setX(x + i);
                ::cubes_render_board[i][j].setY(y+j);
                ::cubes_render_board[i][j].setZ(z);
                glutSolidCube(0.7);
                glPopMatrix();
            }
        }
    }
   
    if(game==1){
        for (int i = 0; i < maxx; i++) {
            for (int j = 0; j < maxy; j++) {
                glPushMatrix();
                glColor3ub(::cubes_render_board[i][j].getRed(),::cubes_render_board[i][j].getGreen(),::cubes_render_board[i][j].getBlue());
                glTranslatef(::cubes_render_board[i][j].getX(), ::cubes_render_board[i][j].getY(), ::cubes_render_board[i][j].getZ());
                //printf(" SUNTETAGMENES KUVOU i=%d j=%d\n",i,j);
                //printf(" x=%f y=%f z=%f",::array[i][j].getX(),::array[i][j].getY(),::array[i][j].getZ());
                glutSolidCube(0.7);
                glPopMatrix();
            }
        }
        /*if (zoom_in) {
            gluLookAt(0, 0, -10.5, 0, 0, -15.5,0, 1, -15.5);
            zoom_in = false;
        }
        if (zoom_out) {
            
            gluLookAt(0, 0, 10.5, 0, 0, -15.5, 0, 1, -15.5);
            
            zoom_out = false;
        }
        if (move_left) {
            gluLookAt(-1, 0, 0,-1, 0, -15.5, 0, 1, -15.5);

            move_left = false;
            
        }
        if (move_right) {
            gluLookAt(1, 0, 0, 1, 0, -15.5, 0, 1, -15.5);
            move_right = false;

        }
        if (move_up) {
            gluLookAt(0, 1, 0, 0, 1, -15.5, 0, 1, -15.5);
            move_up = false;
        }
        if (move_down) {
            gluLookAt(0, -1, 0, 0, -1, -15.5, 0, 1, -15.5);
            move_down = false;
        }*/
    }
    glFlush();
    glutSwapBuffers();
}



void Menu(int choice) {
    if (choice == 1) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        game = 1;
        
    }
    if (choice == 2) {
        exit(0);
    }
    
    glutPostRedisplay();    //for menu option to take immediate effect
}

/* Handler for window re-size event.
Called back when the window first appears and whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {
    // GLsizei for non-negative integer // Compute aspect ratio of the new window
    if (height == 0) height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height; // Set the viewport to cover the new window
    glViewport(0, 0, width, height); // Set the aspect ratio of the clipping volume
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

