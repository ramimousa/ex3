//
// Created by Rami on 1/24/2021.
//

#ifndef EX3_BASEEVENT_H
#define EX3_BASEEVENT_H

namespace mtm {

    class BaseEvent {
        DateWrap event_date;
        string event_name;
        list<int> students_list;
    public:
        BaseEvent(const DateWrap &date, const string &name);

        virtual ~BaseEvent();

        BaseEvent(const BaseEvent &event_to_cpy);

        BaseEvent changeEventDate(int days);

        virtual bool operator==(const BaseEvent &event) const;

        virtual bool operator>(const BaseEvent &event) const;

        virtual bool operator<(const BaseEvent &event) const;

        virtual bool isRegistered(int student) const;

        virtual bool isLegalStudent(int student) const;

        virtual void registerParticipant(int student);

        void unregisterParticipant(int student);

        ostream &printShort(ostream &os);

        ostream &printLong(ostream &os);

        virtual BaseEvent *clone() const = 0;

        string getEventName();

        DateWrap getEventDate();
    };

#endif //EX3_BASEEVENT_H
}