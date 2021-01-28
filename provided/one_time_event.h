#include "event_container.h"
#ifndef EX3_ONE_TIME_EVENT_H
#define EX3_ONE_TIME_EVENT_H
#include <string.h>

namespace mtm {
    template<class BaseEvent>
    class OneTimeEvent : public EventContainer {
    public:
        OneTimeEvent(DateWrap date, string event_name) {
            EventContainer();

        }
        ~OneTimeEvent() = default;
        add(const BaseEvent& event) const override {
            throw NotSupported();
        }
    };
} //namespace mtm
#endif //EX3_ONE_TIME_EVENT_H
