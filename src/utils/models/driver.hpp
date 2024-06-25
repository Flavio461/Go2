#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "user.hpp"
#include "car.hpp"

class driver : public user {
    car *c;
    wchar_t *cnh;
    bool avaliable;
    public:
        driver(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, car*, bool = true);
        ~driver();
        void setCar(car*);
        void setCnh(const wchar_t*);
        car* getCar();
        wchar_t* getCnh();
        bool isAvaliable();
        std::wostream& getOutstreamBuffer(std::wostream&) const override;
};

#endif