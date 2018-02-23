//
// Created by Admin on 21/02/2018.
//

#ifndef SNAKE_GAMEENGINE_H
#define SNAKE_GAMEENGINE_H

#include <conio.h>
#include <afxres.h>
#include "Board.h"

class GameEngine{
private:
    bool quit = false;
    Board* board;
    char lastValidCharInput = 'w'; //initial value for this is 'w';
public:
    GameEngine(int height,int width);
    void Input();
    void processKey(char key);
    void Run();
    char waitForUserInput(int second);
    bool checkValidKey(char c);
};

GameEngine::GameEngine(int height, int width) {
    board = new Board(height,width);
}

void GameEngine::Input() {
    char current = waitForUserInput(1);
    try{
        processKey(current);
    }catch(Snake::GameOverException&) {
        quit = true;
    }
}

void GameEngine::processKey(char key) {
    switch(key){
        case 'w':
            board->MoveSnake(UP);
            break;
        case 's':
            board->MoveSnake(DOWN);
            break;
        case 'd':
            board->MoveSnake(RIGHT);
            break;
        case 'a':
            board->MoveSnake(LEFT);
            break;
    }
}

void GameEngine::Run(){
    while(!quit){
        Input();
        board->Draw();
//        this->board->showSnakeLog();
    }
}

char GameEngine::waitForUserInput(int quarterSeconds) {
    char c = this->lastValidCharInput;
    while(quarterSeconds != 0){
        if(_kbhit()){
            c = _getch();
            if(checkValidKey(c)){
            	this->lastValidCharInput = c;
            }
            break;
        }
        Sleep(100);
        --quarterSeconds;
    }
    return c;
}

bool GameEngine::checkValidKey(char c){
	if(c != 'a' && c != 's' && c!='d' && c!='w'){
		return false;
	}
	return true;
}


#endif //SNAKE_GAMEENGINE_H
