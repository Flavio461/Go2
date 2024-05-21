#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "user.hpp"
#include "car.hpp"

class driver : public user {
    car *c;
    wchar_t *cnh;
    public:
        driver(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, car*);
        ~driver();
        void setCar(car*);
        void setCnh(const wchar_t*);
        car* getCar();
        wchar_t* getCnh();
        std::wostream& getOutstreamBuffer(std::wostream&) const override;
};

#endif