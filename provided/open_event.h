//
// Created by Rami on 1/24/2021.
//
#include "base_event.h"
#ifndef EX3_OPENEVENT_H
#define EX3_OPENEVENT_H
class OpenEvent: public BaseEvent {
public:
    OpenEvent(DateWrap &date, string &name);

    BaseEvent *clone() const override;
};
#endif //EX3_OPENEVENT_H
