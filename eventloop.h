#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <unordered_map>
#include "game.cpp"

namespace event {
    class EventLoop {
        std::unordered_map<unsigned int, void (*)(Direction)> events;

    public:
        EventLoop() = default;

        ~EventLoop() = default;

        void run();

        void addEvent(void (*proc)(Direction), int event_id = 0);

        void delEvent(int event_id);
    };
}


#endif //EVENTLOOP_H
