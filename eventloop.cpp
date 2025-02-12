#include "eventloop.h"
#include <iostream>


void event::EventLoop::addEvent(const int event_id, void (*proc)(int, int, void *)) {
    events[event_id] = proc;
}

void event::EventLoop::delEvent(const int event_id) {
    events.erase(event_id);
}

[[noreturn]] void event::EventLoop::run() {
    char input;
    while (true) {
        std::cin >> input;
        if (input == 'q') {
            break;
        }
        // call the event from the map
        events[input](0, 0, nullptr);
    }
}