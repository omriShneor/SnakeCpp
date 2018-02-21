//
// Created by Admin on 20/02/2018.
//

#ifndef SNAKE_TREAT_H
#define SNAKE_TREAT_H

#include <vector>
#include <cstdlib>
#include "Snake.h"

class Treat{
    int x;
    int y;
private:
public:
    Treat(int x,int y);
    ~Treat(){};
    inline int getX();
    inline int getY();
    void newCoordinate(int x,int y);
};

Treat::Treat(int x, int y):x(x),y(y){}

inline int Treat::getX(){return this->x;}

inline int Treat::getY() {return this->y;}

void Treat::newCoordinate(int x,int y) {
    this->x = x;
    this->y = y;
}

#endif //SNAKE_TREAT_H
