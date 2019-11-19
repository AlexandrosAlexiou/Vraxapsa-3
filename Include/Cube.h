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
        Cube(string texture, int r, int g, int b,double x,double y,double z){
            setCubeTexture(texture);
            setRed(r);
            setGreen(g);
            setBlue(b);
            setX(0);
            setY(0);
            setZ(-10.5);
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
        
    
        void setX(double X){
            x=X;
        }
        double getX(){
            return x;
            
        }
        void setY(double Y){
            y=Y;
        }
        double getY(){
            return y;
        }
        void setZ(double Z){
            z=Z;
        }
        
        double getZ(){
            return z;
        }
    
    //Fields
    private:
        string cubeTexture="nothing";
        int red=0;
        int green=0;
        int blue=0;
        double x;
        double y;
        double z;
    
};
#endif /* Cube_h */
