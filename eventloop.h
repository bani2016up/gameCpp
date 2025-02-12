#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <unordered_map>

namespace event {
    class EventLoop {
        std::unordered_map<unsigned int, void (*)()> events;
    public:
        EventLoop() = default;

        ~EventLoop() = default;

        void run();

        void addEvent(int event_id, void (*proc)());

        void delEvent(int event_id);
    };
}


#endif //EVENTLOOP_H
