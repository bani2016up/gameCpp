#include "eventloop.h"
#include <iostream>


void event::EventLoop::addEvent(Game& game, const int event_id) {
    events[event_id] = game.movePlayer;
}

void event::EventLoop::delEvent(const int event_id) {
    events.erase(event_id);
}

void event::EventLoop::run() {
    char input;
    while (true) {
        std::cin >> input;
        if (input == 'q') {
            break;
        }
        switch (input) {
            case 'w':
                events[0](UP);
                break;
            case 's':
                events[0](DOWN);
                break;
            case 'a':
                events[0](LEFT);
                break;
            case 'd':
                events[0](RIGHT);
                break;
            default: {
                break;
            }
        }
    }
}