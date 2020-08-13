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
        Cube(char * texture, int r, int g, int b,double x,double y,double z){
            texture = (char*)malloc(15*sizeof(char));
            setCubeTexture(texture);
            setRed(r);
            setGreen(g);
            setBlue(b);
            setX(x);
            setY(y);
            setZ(z);
        }
    
        //Questions
        bool isBlue()
        {
            if (blue == 255 && red == 0 && green == 0)
            {
                return true;
            }
            return false;
        }
        bool isRed()
        {
            if (blue == 0 && red == 255 && green == 0)
            {
                return true;
            }
            return false;
        }
        bool isRock()
        {
            if (strcmp(cubeTexture,"Rock") == 0)
            {
                return true;
            }
            return false;
        }
        bool isPaper()
        {
            if (strcmp(cubeTexture, "Paper") == 0)
            {
                return true;
            }
            return false;
        }
        bool isScissor()
        {
            if (strcmp(cubeTexture, "Scissor") == 0)
            {
                return true;
            }
            return false;
        }
        bool isItem() {
            if (strcmp(cubeTexture, "nothing")!=0) {
                return true;
            }
            return false;
        
        }
    
        // Getters-Setters
        void setCubeTexture(char* texture){
            cubeTexture=texture;
        }
        char* getCubeTexture(){
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
        char *cubeTexture;
        int red=0;
        int green=0;
        int blue=0;
        double x;
        double y;
        double z;
    
};
#endif /* Cube_h */
