//
// Created by Rami on 1/24/2021.
//
#include <iostream>
using  namespace std;
using std::string ;
#include "date_wrap.h"
#include "exceptions.h"
#include "base_event.h"
#define MAX_STUDENT_NUM 1234567890

#ifndef EX3_EVENTCONTAINER_H
#define EX3_EVENTCONTAINER_H

namespace mtm {

class EventContainer{
    list<BaseEvent*> events_list;
protected:
    List<BaseEvent*> getEventsList();
public:
    EventContainer() = default;
    virtual ~EventContainer() {};
    virtual add(const BaseEvent& event) const = 0;
    class EventIterator {
        EventContainer* event_container;
        BaseEvent* current_iterator;
    public:
        EventIterator(EventContainer& ec, BaseEvent& be);
        ~EventIterator() = default;
        EventIterator(const EventContainer& container,const BaseEvent& event);
        EventIterator& operator=(const EventContainer::EventIterator& iterator);
        EventIterator& operator++();
        bool operator==(EventContainer::EventIterator t1);
        bool operator!=(EventContainer::EventIterator t1);
        BaseEvent& operator*();
    };
    EventIterator begin();
    EventIterator end();
};

#endif //EX3_EVENTCONTAINER_H
}