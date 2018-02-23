//
// Created by Admin on 20/02/2018.
//

#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H


#include <iostream>
#include "Snake.h"
#include "Treat.h"

class Board {
private:
    int height,width;
    Snake* snake;
    Treat* treat;
    int score = 0;
    void GenerateNewCoordinates(int* x,int* y);
public:
    Board(int height,int width);
    ~Board();
    void Draw();
    std::pair<int,int> RandomCoordinate();
    void MoveSnake(Direction direction);
    bool checkCollisionSnakeWithBoard();
    Direction SnakeCurrentDirection();
    void showSnakeLog();
};

Board::Board(int height,int width):height(height),width(width) {
    snake = new Snake((width/2)-1,(height/2)-1,UP);
    std::pair<int, int> pair = RandomCoordinate();
    treat = new Treat(pair.first,pair.second);
}

Board::~Board() {
    delete snake;
    delete treat;
}

void Board::Draw() {
    system("cls");
    for(int i = 0; i < height; i++){
        for(int j = 0 ; j < width; j++){
            if(j == 0 || j == width-1 || i == 0 || i == height-1){
                std::cout << "\xB2";
            }else if(snake->isCoordinatePartOfSnake(std::pair<int,int>(j,i))){
                std::cout<<"\xDB";
            }else if(treat->getX()==j && treat->getY()==i){
                std::cout << "\x9D";
            } else{
                std::cout<< " ";
            }
        }
        std::cout<<"\n";
    }
    std::cout << "Your current score is: " << this->score << std::endl;
}

std::pair<int,int> Board::RandomCoordinate(){
    int temp_x,temp_y;
    this->GenerateNewCoordinates(&temp_x,&temp_y);
    while(snake->isCoordinatePartOfSnake(std::pair<int,int>(temp_x,temp_y))){
    	this->GenerateNewCoordinates(&temp_x,&temp_y);
    }
    return std::pair<int,int>(temp_x,temp_y);
}

void Board::GenerateNewCoordinates(int* x,int* y){
	*x = rand()%(width-1) + 1;
	*y = rand()%(height-1) + 1;
}

bool Board::checkCollisionSnakeWithBoard() {
    if(snake->currCoordinate().first == 0 || snake->currCoordinate().first == width-1 || snake->currCoordinate().second == 0 ||
            snake->currCoordinate().second == height-1){
        return true;
    }
    return false;
}

void Board::MoveSnake(Direction direction){
    snake->changeDirection(direction);
    snake->moveSnake();
    if(snake->checkTreatEaten(treat)){
        snake->IncreaseSnakeLength();
		std::pair<int, int> newTreatCoordinate = RandomCoordinate();
		treat->newCoordinate(newTreatCoordinate.first,newTreatCoordinate.second);
		this->score +=10;
    }else if(checkCollisionSnakeWithBoard()){
        throw Snake::GameOverException();
    }
    return;
}

Direction Board::SnakeCurrentDirection() {
    return snake->getDirection();
}

void Board::showSnakeLog(){
    this->snake->printSnakeLog();
}

#endif //SNAKE_BOARD_H
