//
//

#ifndef EX3_DATE_WRAP_H
#define EX3_DATE_WRAP_H
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
extern "C" {

#include "date.h"

}

namespace mtm {
    class DateWrap {
        Date date;

    public:

        DateWrap(int day, int month, int year);

        virtual ~DateWrap();

        DateWrap(const DateWrap &date1);

        int day();

        int month();

        int year();

        friend ostream &operator<<(ostream &os, const DateWrap &date1);

        DateWrap operator=(const DateWrap &date1);

        bool operator<(const DateWrap &date1);

        bool operator>(const DateWrap &date1);

        bool operator==(const DateWrap &date1);

        bool operator<=(const DateWrap &date1);

        bool operator>=(const DateWrap &date1);

        bool operator!=(const DateWrap &date1);

        DateWrap operator+=(int days);

        DateWrap operator+(const int days);

        DateWrap operator++(int);
    };

    DateWrap operator+(const int days, const DateWrap date1);
}//namespace
#endif //EX3_DATE_WRAP_H
