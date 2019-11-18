//
//  Cube.h
//  VraXaPsa3
//
//  Created by Alexandros Alexiou on 16/11/19.
//  Copyright © 2019 Alexandros Alexiou. All rights reserved.
//
#include <iostream>
#include <string>

using namespace std;

#ifndef Cube_h
#define Cube_h

class Cube{
    
    public:
        //Default Constructor
        Cube() = default;
        //Constructor
        Cube(string texture, int r, int g, int b){
            setCubeTexture(texture);
            setRed(r);
            setGreen(g);
            setBlue(b);
        }
        // Getters-Setters
        void setCubeTexture(string texture){
            cubeTexture=texture;
        }
        string getCubeTexture(){
            return cubeTexture;
        }
    
        void setRed(int r){
            red=r;
        }
        int getRed(){
            return red;
        }
    
        void setGreen(int g){
            green=g;
        }
        int getGreen(){
            return green;
        }
    
        void setBlue(int b){
            blue=b;
        }
    
        int getBlue(){
            return blue;
        }
    
    //Fields
    private:
        string cubeTexture="nothing";
        int red=0;
        int green=0;
        int blue=0;
};
#endif /* Cube_h */
