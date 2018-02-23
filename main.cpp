#include <iostream>
#include "GameEngine.h"

int main() {
    GameEngine* engine = new GameEngine(25,40);
    engine->Run();
    return 0;
}
