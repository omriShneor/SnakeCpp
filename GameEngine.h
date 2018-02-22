//
// Created by Admin on 21/02/2018.
//

#ifndef SNAKE_GAMEENGINE_H
#define SNAKE_GAMEENGINE_H

#include <conio.h>
#include "Board.h"

class GameEngine{
private:
    bool quit = false;
    Board* board;
public:
    GameEngine(int height,int width);
    void Input();
    void processKey(char key);
    void Run();
};

GameEngine::GameEngine(int height, int width) {
    board = new Board(height,width);
}

void GameEngine::Input() {
    if(_kbhit()){
        char current = _getch();
        try{
            processKey(current);
        }catch(Snake::GameOverException) {
            quit = true;
        }
    }else{
        board->MoveSnake(board->SnakeCurrentDirection());
    }
}

void GameEngine::processKey(char key) {
    switch(key){
        case 'w':
            board->MoveSnake(UP);
        case 's':
            board->MoveSnake(DOWN);
        case 'd':
            board->MoveSnake(RIGHT);
        case 'a':
            board->MoveSnake(LEFT);
    }
}

void GameEngine::Run(){
    while(!quit){
        Input();
//        board->Draw();
        this->board->showSnakeLog();
    }
}


#endif //SNAKE_GAMEENGINE_H
