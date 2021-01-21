//
// Created by Rami on 1/20/2021.
//

#ifndef EX3_EXCEPTIONS_H
#define EX3_EXCEPTIONS_H

namespace mtm {
    class Exception : public std::exception{};
    class NegativeDays : public Exception{};
}

#endif //EX3_EXCEPTIONS_H
