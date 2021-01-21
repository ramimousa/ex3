//
//

#ifndef EX3_DATE_WRAP_H
#define EX3_DATE_WRAP_H
#include <iostream>
using std::cout;
using std::endl;
extern "C" {

    #include "date.h"

}

class DateWrap {
    Date date;

public:
    DateWrap(int day, int month = 0 , int year = 0);
    ~DateWrap();
    int day();
    int month();
    int year();
    friend ostream& operator<<(ostream& os, const DateWrap& date);
    bool operator<(const DateWrap& date1);
    bool operator>(const DateWrap& date1);
    bool operator==(const DateWrap& date1);
    bool operator<=(const DateWrap& date1);
    bool operator>=(const DateWrap& date1);
    bool operator!=(const DateWrap& date1);

    DateWrap operator+(int days) const;
    DateWrap operator+=(int days);
    DateWrap operator++(int);


};
#endif //EX3_DATE_WRAP_H
