#include <iostream>
#include "game.cpp"
#include "eventloop.h"


int main() {
    Game game;
    event::EventLoop eventLoop;
    eventLoop.addEvent(()[]{}, 0);
    eventLoop.run();
    game.quit();
    return 0;
}
