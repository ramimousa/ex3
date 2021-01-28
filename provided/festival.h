//
// Created by Rami on 1/22/2021.
//
#include "heade_files.h"
#include "date_wrap.h"
#ifndef EX3_FESTIVAL_H
#define EX3_FESTIVAL_H

namespace mtm {

    class Festival : public EventContainer {
    DateWrap date;
    public:
    festival(DateWrap festivalDate) :
    EventContainer(),
    date(festivalDate) {}
    virtual ~festival() = default;
    add(const BaseEvent& event) const override {
        if (date != event.get_event_date()) {
            throw DateMismatch();
        }
        list<BaseEvent*> list = getEventsList();
        list.add(event&);
    }
    };
}//namespace mtm

#endif //EX3_FESTIVAL_H
