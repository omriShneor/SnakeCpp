#include <iostream>
#include "GameEngine.h"

int main() {
    GameEngine* engine = new GameEngine(40,20);
    engine->Run();
    return 0;
}