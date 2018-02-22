//
// Created by Admin on 20/02/2018.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <utility>
#include <queue>
#include "Board.h"
#include "Treat.h"

enum Direction {UP = 0,DOWN = 1,LEFT = 2, RIGHT = 3};

class Snake{
private:
    int curr_x,curr_y;
    Direction direction;
    std::vector<std::pair<int,int>>* SnakeCoordinates;
public:
    Snake(int x,int y,Direction dir);
    ~Snake();
    void checkColisionWithSelf(std::pair<int,int> newCoord);
    std::pair<int,int> currCoordinate();
    std::pair<int, int> IncreaseSnakeLength();
    void moveSnake();
    inline void changeDirection(Direction dir);
    inline Direction getDirection(){return this->direction;};
    bool checkTreatEaten(Treat* treat);
    class GameOverException{};
    bool isCoordinatePartOfSnake(std::pair<int, int> newCoord);
    void printSnakeLog();
};

Snake::Snake(int x,int y,Direction dir) : direction(dir){
    curr_x = x,curr_y = y;
    SnakeCoordinates = new std::vector<std::pair<int,int>>;
    SnakeCoordinates->insert(SnakeCoordinates->begin(),std::pair<int,int>(x,y));
}

Snake::~Snake(){
    delete SnakeCoordinates;
}


void Snake::moveSnake() {
    const std::pair<int, int> &pair = IncreaseSnakeLength();
    this->SnakeCoordinates->pop_back();
    //this->checkColisionWithSelf(pair); what's the logic behind this?
}

std::pair<int,int> Snake::IncreaseSnakeLength() {
    std::pair<int,int> coordinate;
    switch(this->direction){
        case UP:
            coordinate.first = curr_x;
            coordinate.second = curr_y - 1;
            curr_y = curr_y - 1;
            break;
        case DOWN:
            coordinate.first = curr_x;
            coordinate.second = curr_y + 1;
            curr_y = curr_y + 1;
            break;
        case LEFT:
            coordinate.first = curr_x - 1;
            coordinate.second = curr_y;
            curr_x = curr_x - 1;
            break;
        case RIGHT:
            coordinate.first = curr_x + 1;
            coordinate.second = curr_y;
            curr_x = curr_x + 1;
            break;
    }
    this->checkColisionWithSelf(coordinate);
    SnakeCoordinates->insert(SnakeCoordinates->begin(),coordinate);
    return coordinate;
}

void Snake::changeDirection(Direction dir) {
    this->direction = dir;
}

bool Snake::checkTreatEaten(Treat *treat) {
    if(treat->getX() == this->SnakeCoordinates->front().first && treat->getY() == this->SnakeCoordinates->front().second){
        return true;
    }
    return false;
}

std::pair<int, int> Snake::currCoordinate() {
    return std::pair<int, int>(this->curr_x,this->curr_y);
}

void Snake::checkColisionWithSelf(std::pair<int,int> newCoord) {
    for(std::pair<int,int> coordinates : *SnakeCoordinates){
        if(newCoord==coordinates){
            throw new GameOverException();
        }
    }
    return;
}

bool Snake::isCoordinatePartOfSnake(std::pair<int,int> newCoord) {
    for(std::pair<int,int> coordinates : *SnakeCoordinates){
        if(newCoord==coordinates){
            return true;
        }
    }
    return false;
}

void Snake::printSnakeLog() {
    for(std::pair<int,int> coordinate : *SnakeCoordinates){
        std::cout << coordinate.first +  "," + coordinate.second << std::endl;
    }
}


#endif //SNAKE_SNAKE_H
