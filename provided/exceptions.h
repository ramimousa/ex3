//
// Created by Rami on 1/20/2021.
//

#ifndef EX3_EXCEPTIONS_H
#define EX3_EXCEPTIONS_H

namespace mtm {
    class Exception : public std::exception{};
    class NegativeDays : public Exception{};
    class InvalidDate : public Exception{};
    class DateMismatch : public Exception{};
    class AlreadyRegistered : public Exception{};
    class RegistrationBlocked: public Exception{};
    class NotRegistered: public Exception{};
    class AlreadyInvited: public Exception{};
    class InvalidNumber: public Exception{};
    class InvalidInterval: public Exception{};
    class NotSupported: public Exception{};
}


#endif //EX3_EXCEPTIONS_H
