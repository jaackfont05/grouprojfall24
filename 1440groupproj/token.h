//Mason Crippen
//Jack Fontenot
//Connor Griffin
//Andrei Kuvshinikov


#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include "line.h"

class token{
private:
    int radius;
    point center;
    color _color;
    point secPoint(int deg, point c){
        point p;
        double rad = deg * M_PI / 180.0;

        p.x = static_cast<int>(radius * cos(rad)) + c.x;
        p.y = static_cast<int>(radius * sin(rad)) + c.y;

        return p;
    }

public:
    token();
    token(int r, color c, point p);
    void setColor(color c);
    color getColor();
    void setCenter(point p);
    point getCenter();
    void setRadius(int r);
    int getRadius();
    void draw(SDL_Plotter& g);
    void erase(SDL_Plotter& g,color c);
};

#endif // TOKEN_H_INCLUDED
