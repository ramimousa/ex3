#include <iostream>
using  namespace std;
using std::string ;
#include <string.h>
#include <stdio.h>
#include "base_event.h"
#include "closed_event.h"
#include "custom_event.h"
#include "date_wrap.h"
#include "exceptions.h"
#include "open_event.h"
#include "event_container.h"
#include "festival.h"
#include "recurring_event.h"
#define MAX_STUDENT_NUM 1234567890

namespace mtm {

    template<class T>
    struct node
    {
        T data;
        struct node *next;
    };

    template<class T>
    class list
    {
    public:
        node<T> *head, *tail;
        int size;
        list()
        {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        T getHead() const;
        T getTail() const;
        void add(const T& new_data);
        void add(const T& new_data, )
        void remove(const T& old_data);
        ostream& printList(ostream& os) const;
        bool isExists(const T& data) const;
        int getSize() const;
    };
    template<class T>
    bool list<T>::isExists(const T &data) const {
        node<int>* ptr = head;
        while(ptr != tail){
            if(ptr->data == data){
                return true;
            }
            ptr = ptr->next;
        }
        if(tail->data == data){
            return true;
        }
        return false;
    }
    template<class T>
    T list<T>::getHead() const {
        return head->data;
    }
    template<class T>
    T list<T>::getTail() const {
        return tail->data;
    }
    template<class T>
    int list<T>::getSize() const{
        return size;
    }
    template<class T>
    void list<T>::add(const T& data) {
        node<T>* tmp = new node<T>();
        tmp->data = data;
        tmp->next = nullptr;
        if(head == nullptr){
            tail = tmp;
            head = tmp;
            size++;
        }else if(head->data > data){
            tmp->next = head;
            head = tmp;
            size++;
        }else if(tail->data < data){
            tail->next = tmp;
            tail = tmp;
            size++;
        }else{
            node<T>* ptr = head;
            while(ptr != tail){
                if(ptr->next->data > data){
                    tmp->next = ptr->next;
                    ptr->next = tmp;
                    size++;
                    return;
                }
                ptr = ptr->next;
            }
        }
    }
    template<class T>
    void list<T>::remove(const T& old_data) {
        if(size != 0) {
            node<T> *ptr =head;
            if (head->data == old_data) {
                head = head->next;
                delete ptr;
                size--;
                return;
            }
            for (int i = 1; i < size; i++) {
                if (ptr->next->data == old_data) {
                    node<T> *to_delete = ptr->next;
                    ptr->next = ptr->next->next;
                    delete to_delete;
                    if(i == size - 1){
                        tail = ptr;
                    }
                    size--;
                    return;
                }
                ptr = ptr->next;
            }
        }
    }
    template<class T>
    ostream& list<T>::printList(ostream& os) const{
        node<T>* ptr = head;
        while (ptr != tail){
            os <<ptr->data<<endl;
            ptr = ptr->next;
        }
        os<<tail->data<<endl;
        return os;
    }
//************************implementation:BaseEvent****************************
    BaseEvent::BaseEvent(const DateWrap& date,const string& name):event_date(date),event_name(name){}

    BaseEvent::~BaseEvent() {
        int size = students_list.getSize();
        if(size != 0){
            for(int i=0; i<size; i++){
                students_list.remove(students_list.getHead());
            }
        }
    }

    BaseEvent::BaseEvent(const BaseEvent& event_to_cpy):event_date(event_to_cpy.event_date),
                                                        event_name(event_to_cpy.event_name){
        node<int>* ptr = event_to_cpy.students_list.head;
        node<int>* end = event_to_cpy.students_list.tail;
        while(ptr != end){
            students_list.add(ptr->data);
            ptr = ptr->next;
        }
        students_list.add(end->data);
    }

    BaseEvent BaseEvent::changeEventDate(int days) {
        event_date += days;
        return *this;
    }

    bool BaseEvent::isLegalStudent(int student) const{
        if(student < 1 || student > MAX_STUDENT_NUM){
            throw InvalidSudent();
        }
        if(isRegistered(student)){
            throw AlreadyRegistered();
        }
        return true;
    }

    bool BaseEvent::isRegistered(int student) const{
        return students_list.isExists(student);
    }
    void BaseEvent::registerParticipant(int student) {
        if(isLegalStudent(student)){
            students_list.add(student);
        }
    }
    void BaseEvent::unregisterParticipant(int student) {
        if(!isRegistered(student)){
            throw NotRegistered;
        }
        students_list.remove(student);
    }
    ostream& BaseEvent::printShort(ostream &os) {
        os << event_name << " " << event_date<<endl;
        return os;
    }
    ostream& BaseEvent::printLong(ostream &os) {
        return students_list.printList(printShort(os));
    }
    bool BaseEvent::operator==(const BaseEvent& event) const{
        return (event_name==event.event_name && event.event_date==event_date)
    }
    bool BaseEvent::operator>(const BaseEvent &event) const{
        if(event_date == event.event_date){
            return event_name>event.event_name;
        }
        return event_date>event.event_date;
    }
    bool BaseEvent::operator<(const BaseEvent &event) const {
        if(event_date == event.event_date){
            return event_name<event.event_name;
        }
        return event_date<event.event_date;
    }

    string BaseEvent::getEventName() {
        return this->event_name;
    }

    DateWrap BaseEvent::getEventDate() {
        return this->event_date;
    }
//*******************************implementation OpenEvent******************
    OpenEvent::OpenEvent(DateWrap &date, string &name): BaseEvent(date,name){}

    BaseEvent* OpenEvent::clone() const {
        return new OpenEvent(*this);
    }
//*************************implementation ClosedEvent****************
    ClosedEvent::ClosedEvent(DateWrap &date, string &name): BaseEvent(date,name){}

    ClosedEvent::ClosedEvent(const ClosedEvent &event_to_cpy): BaseEvent(event_to_cpy){
        node<int>* ptr = event_to_cpy.invitees.head;
        node<int>* end = event_to_cpy.invitees.tail;
        while(ptr != end){
            invitees.add(ptr->data);
            ptr = ptr->next;
        }
        invitees.add(end->data);
    }
    ClosedEvent::~ClosedEvent(){
        int size = invitees.getSize();
        if(size != 0){
            for(int i=0; i<size; i++){
                invitees.remove(invitees.getHead());
            }
        }
    }
    bool ClosedEvent::isInvited(int student) const{
        return invitees.isExists(student);
    }
    void ClosedEvent::addInvitee(int student) {
        if(!isLegalStudent(student)){
            throw InvalidSudent();
        }
        if(isInvited(student)){
            throw AlreadyInvited();
        }
        invitees.add(student);
    }
    bool ClosedEvent::isLegalStudent(int student) const {
        if(BaseEvent::isLegalStudent(student)){
            if(isInvited(student)){
                return true;
            }
            throw RegistrationBlocked();
        }
    }
    BaseEvent* ClosedEvent::clone() const {
        return new ClosedEvent(*this);
    }
//******************************implementation CustomEvent******************
    template<class CanRegister>
    CustomEvent<CanRegister>::
    CustomEvent(const DateWrap &date, const string &name,const CanRegister &condition):
            BaseEvent(date,name),condition(condition){}
    template<class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const CustomEvent<CanRegister> &event_to_copy):
            BaseEvent(event_to_copy){
        condition = event_to_copy.condition;
    }
    template<class CanRegister>
    bool CustomEvent<CanRegister>::isLegalStudent(int student) const {
        if(BaseEvent::isLegalStudent(student)){
            if(condition(student)){
                return true;
            }
            return false;
        }
    }
    template<class CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const {
        return new CustomEvent<CanRegister>(*this);
    }
//******************************implementation eventContainer******************
    EventContainer::EventIterator::EventIterator(EventContainer& ec, BaseEvent& be) {
        event_container = &ec;
        if (EventContainer.events_list.getSize() == 0 ) {
            current_iterator = nullptr;
        }
        current_iterator = &ec.eventslist.getHead();
        while (current_iterator != &ev.eventslist.getTail() ) {
            if (current_iterator* = be) {
                current_iterator = &be;
                break;
            }
            current_iterator = current_iterator->next;
        }
        current_iterator = &ec.eventslist.getHead();
    }

    EventContainer::EventIterator::EventIterator(const EventContainer& container,const BaseEvent& event) {
        event_container = &container;
        current_iterator = &event;
    }

    EventIterator& EventContainer::EventIterator::operator=(const EventContainer::EventIterator& iterator){
        event_container = iterator.event_container;
        current_iterator = iterator.current_iterator;
    }

    List<BaseEvent*> EventContainer::getEventsList() {
        return events_list;
    }

    EventContainer& EventContainer::EventIterator::operator++() {
        current_iterator = currentiterator->next;
        return *current_iterator;
    }

    bool EventContainer::EventIterator::operator==(EventContainer::EventIterator t1) {
        if (*current_iterator == t1->current_iterator) {
            if (event_container == t1->event_container) {
                return true;
            }
        }
        return false;
    }

    bool EventContainer::EventIterator::operator!=(EventContainer::EventIterator t1) {
        if (this == t1) {
            return false;
        } else return true;
    }

    BaseEvent& EventContainer::EventIterator::operator*() {
        return *current_iterator;
    }

    EventIterator EventContainer::begin() {
        EventIterator iterator(EventIterator(this->events_list, this->events_list->head));
        return iterator;
    }

    EventIterator EventContainer::end() {
        EventIterator iterator(EventIterator(this->events_list, this->events_list->tail));
        return iterator;
    }
    //******************************implementation RecurringEvent******************
    template <class BaseEvent>
    RecurringEvent<BaseEvent>::
    RecurringEvent(DateWrap first_date, string event_name, int occurrences_num, int days_interval) {
        if (occurrences_num < 1) {
            throw InvalidNumber();
        }
        if (days_interval < 1) {
            throw InvalidInterval();
        }
        EventContainer();
        max_size = occurrences_num;
        size = 0;
        for (int i = 0; i < occurrences_num; ++i) {
            if (i == 0) {
                BaseEvent tmp_event(first_date, event_name);
            }
            else {
                tmp_event.changeEventDate(days_interval);
            }
            add(tmp_event&);
            size++;
        }
    }
}// namespace mtm