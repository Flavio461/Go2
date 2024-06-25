#include "dataBaseAPI.hpp"
#include <cstring>
#include "SHA256.hpp"

/*
#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>

class car {
    int id;
    wchar_t *model, *plate;
    public:
        car(int id, const wchar_t* model, const wchar_t* plate);
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
        std::wostream& getOutstreamBuffer(std::wostream&) const override;
};

#endif

#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class user {
protected:   
    int id;
    wchar_t *name, *email, *phone;
public:
    user(const wchar_t*, const wchar_t*, const wchar_t*);
    ~user();
    void setName(const wchar_t*);
    void setEmail(const wchar_t*);
    void setPhone(const wchar_t*);
    int getId();
    wchar_t* getName();
    wchar_t* getEmail();
    wchar_t* getPhone();
    virtual std::wostream& getOutstreamBuffer(std::wostream&) const;
    friend std::wostream& operator<<(std::wostream&, const user&); //Acessa os membros privados da classe
};

#endif
*/

void writeString(std::fstream& out, const wchar_t* str) {
    const char* str2 = utf8_encode(std::wstring(str)).c_str();
    size_t size = std::strlen(str2);
    out.write((char*)&size, sizeof(size_t));
    out.write(str2, size);
}

const wchar_t* readString(std::fstream& in) {
    size_t size;
    in.read((char*)&size, sizeof(size_t));
    char *str = new char[size+1];
    in.read(str, size);
    str[size] = '\0';
    return wcsdup((utf8_decode(std::string(str))).c_str());
}

dataBase::dataBase() {
    userFile.open(USER_FILE_PATH, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
    driverFile.open(DRIVER_FILE_PATH, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
} 

void dataBase::writeUser(user *u, std::string password) {
    int id = u->getId();
    userFile.write(reinterpret_cast<const char*>(&id), sizeof(int));
    writeString(userFile, u->getName());
    writeString(userFile, u->getEmail());
    writeString(userFile, u->getPhone());
    userFile << password;
    userFile.flush();
}

void dataBase::writeDriver(driver *d, std::string password) {
    int id = d->getId();
    driverFile.write(reinterpret_cast<const char*>(&id), sizeof(int));
    writeString(driverFile, d->getName());
    writeString(driverFile, d->getEmail());
    writeString(driverFile, d->getPhone());
    writeString(driverFile, d->getCnh());
    writeString(driverFile, d->getCar()->getModel());
    writeString(driverFile, d->getCar()->getPlate());
    driverFile << password;
    driverFile.flush();
}

std::vector<user*> dataBase::readUsers() {
    std::vector<user*> users;
    userFile.clear();
    userFile.seekg(0, std::ios::beg);
    while (true) {
        int id;
        userFile.read((char*)&id, sizeof(int));
        if (userFile.eof()) break;
        user *newUser = new user(L"", L"", L"", id);
        const wchar_t* name = readString(userFile);
        const wchar_t* email = readString(userFile);
        const wchar_t* phone = readString(userFile);
        newUser->setName(name);
        newUser->setEmail(email);
        newUser->setPhone(phone);
        char* pass = new char[65];
        userFile.read(pass, 64);
        pass[64] = '\0';
        users.push_back(newUser);
    }
    return users;
}

std::vector<user*> dataBase::readDrivers() {
    std::vector<user*> drivers;
    driverFile.clear();
    driverFile.seekg(0, std::ios::beg);
    while (true) {
        int id;
        driverFile.read((char*)&id, sizeof(int));
        if (driverFile.eof()) break;
        driver *newDriver = new driver(L"", L"", L"", L"", nullptr);
        const wchar_t* name = readString(driverFile);
        const wchar_t* email = readString(driverFile);
        const wchar_t* phone = readString(driverFile);
        const wchar_t* cnh = readString(driverFile);
        const wchar_t* model = readString(driverFile);
        const wchar_t* plate = readString(driverFile);
        newDriver->setName(name);
        newDriver->setEmail(email);
        newDriver->setPhone(phone);
        ((driver*)newDriver)->setCnh(cnh);
        ((driver*)newDriver)->setCar(new car(model, plate));
        char* pass = new char[65];
        driverFile.read(pass, 64);
        pass[64] = '\0';
        drivers.push_back(newDriver);
    }
    return drivers;
}

user* dataBase::getUser(std::wstring e, std::string password) {
    userFile.clear();
    userFile.seekg(0, std::ios::beg);
    while (true) {
        int id;
        userFile.read((char*)&id, sizeof(int));
        if (userFile.eof()) break;
        user *newUser = new user(L"", L"", L"", id);
        const wchar_t* name = readString(userFile);
        const wchar_t* email = readString(userFile);
        const wchar_t* phone = readString(userFile);
        newUser->setName(name);
        newUser->setEmail(email);
        newUser->setPhone(phone);
        char* pass = new char[65];
        userFile.read(pass, 64);
        pass[64] = '\0';
        if (wcscmp(email, e.c_str())) continue;
        if (!strcmp(pass, password.c_str())) return newUser;
    }
    return nullptr;
}

driver* dataBase::getDriver(std::wstring e, std::string password) {
    driverFile.clear();
    driverFile.seekg(0, std::ios::beg);
    while (true) {
        int id;
        driverFile.read((char*)&id, sizeof(int));
        if (driverFile.eof()) break;
        driver *newDriver = new driver(L"", L"", L"", L"", nullptr);
        const wchar_t* name = readString(driverFile);
        const wchar_t* email = readString(driverFile);
        const wchar_t* phone = readString(driverFile);
        const wchar_t* cnh = readString(driverFile);
        const wchar_t* model = readString(driverFile);
        const wchar_t* plate = readString(driverFile);
        newDriver->setName(name);
        newDriver->setEmail(email);
        newDriver->setPhone(phone);
        ((driver*)newDriver)->setCnh(cnh);
        ((driver*)newDriver)->setCar(new car(model, plate));
        char* pass = new char[65];
        driverFile.read(pass, 64);
        pass[64] = '\0';
        if (email != e) continue;
        if (pass == password.c_str()) return newDriver;
    }
    return nullptr;
}

dataBase::~dataBase() {
    userFile.close();
    driverFile.close();
}