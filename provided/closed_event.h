//
// Created by Rami on 1/24/2021.
//
#include "base_event.h"
#ifndef EX3_CLOSED_EVENT_H
#define EX3_CLOSED_EVENT_H

namespace mtm {

    class ClosedEvent : public BaseEvent {
        list<int> invitees;
    public:
        ClosedEvent(DateWrap date, string name);

        ClosedEvent(const ClosedEvent &event_to_cpy);

        ~ClosedEvent() override;

        void addInvitee(int student);

        bool isInvited(int student) const;

        bool isLegalStudent(int student) const override;

        BaseEvent *clone() const override;
    };

#endif //EX3_CLOSED_EVENT_H
}