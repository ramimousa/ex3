//
// Created by Rami on 1/24/2021.
//
#include "base_event.h"
#ifndef EX3_CUSTOMEVENT_H
#define EX3_CUSTOMEVENT_H

namespace mtm {

    template<class CanRegister>
    class CustomEvent : public BaseEvent {
        CanRegister condition;
    public:
        CustomEvent(const DateWrap &date, const string &name, const CanRegister &condition);

        CustomEvent(const CustomEvent<CanRegister> &event_to_copy);

        bool isLegalStudent(int student) const override;

        BaseEvent *clone() const override;
    };

#endif //EX3_CUSTOMEVENT_H
}