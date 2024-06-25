#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>

class car {
    int id;
    wchar_t *model, *plate;
    public:
        car(const wchar_t* model, const wchar_t* plate);
        ~car();
        void setModel(const wchar_t* model);
        void setPlate(const wchar_t* plate);
        int getId();
        wchar_t* getModel();
        wchar_t* getPlate();
        std::wostream& getOutstreamBuffer(std::wostream& out) const;
        friend std::wostream& operator<<(std::wostream& out, const car& c);
};

#endif