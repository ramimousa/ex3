//
// Created by Rami on 1/26/2021.
//
#include "event_container.h"
#include <string.h>
#ifndef EX3_RECURRING_EVENT_H
#define EX3_RECURRING_EVENT_H

namespace mtm {
    template <class BaseEvent>
    class RecurringEvent : public EventContainer {
        int max_size;
        int size;
    public:
        RecurringEvent(DateWrap first_date, string event_name, int occurrences_num, int days_interval);
        ~RecurringEvent() = default;
        add(const BaseEvent& event) const override {
            if (size == max_size) {
                throw NotSupported();
            }
            list<BaseEvent*> list = getEventsList();
            list.add(event&);
        }
    };
}



#endif //EX3_RECURRING_EVENT_H
