#include "date_wrap.h"
#include "exceptions.h"

namespace mtm {

    DateWrap::DateWrap(int day, int month, int year) {
        if (day < 1 || day > 30 || month < 1 || month > 12 || year < 0) {
            throw InvalidDate();
        }
        date = dateCreate(day, month, year);
        return;
    }

    DateWrap::~DateWrap() {
        dateDestroy(date);
        return;
    }

    DateWrap::DateWrap(const DateWrap &date1) {
        int day, month, year;
        dateGet(date1.date, &day, &month, &year);
        date = dateCreate(day, month, year);
        return;
    }

    int DateWrap::day() {
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return day;
    }

    int DateWrap::month() {
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return month;
    }

    int DateWrap::year() {
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return year;
    }

    ostream &operator<<(ostream &os, const DateWrap &date1) {
        int day, month, year;
        dateGet(date1.date, &day, &month, &year);
        return os << day << "/" << month << "/" << year ;
    }

    bool DateWrap::operator<(const DateWrap &date1) {
        int tmp = dateCompare(date, date1.date);
        return (tmp < 0);

    }

    bool DateWrap::operator>(const DateWrap &date1) {
        int tmp = dateCompare(date, date1.date);
        return (tmp > 0);
    }

    bool DateWrap::operator==(const DateWrap &date1) {
        int tmp = dateCompare(date, date1.date);
        return (tmp == 0);
    }

    bool DateWrap::operator<=(const DateWrap &date1) {
        return (*this < date1 || *this == date1);
    }

    bool DateWrap::operator>=(const DateWrap &date1) {
        return (*this < date1 || *this == date1);
    }

    bool DateWrap::operator!=(const DateWrap &date1) {
        return (*this > date1 || *this > date1);
    }

    DateWrap DateWrap::operator=(const DateWrap &date1) {
        int day, month, year;
        dateGet(date1.date, &day, &month, &year);
        date = dateCreate(day, month, year);
        return *this;
    }

    DateWrap DateWrap::operator+=(int days) {
        if (days < 0) {
            throw NegativeDays();
        }
        for (int i = 0; i < days; i++) {
            dateTick(date);
        }
        return *this;
    }

    DateWrap DateWrap::operator+(const int days) {
        DateWrap newDate = *this;
        return newDate += days;
    }

    DateWrap operator+(const int days, const DateWrap date1) {
        if (days < 0) {
            throw NegativeDays();
        }
        DateWrap newDate = date1;
        return newDate += days;
    }

    DateWrap DateWrap::operator++(int) {
        DateWrap tmp = *this;
        dateTick(date);
        return tmp;
    }

} // namespace mtm