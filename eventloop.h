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

        void delEvent(int event_id);

        void addEvent(void(* proc)(Direction diraction), int event_id);
    };
}


#endif //EVENTLOOP_H
