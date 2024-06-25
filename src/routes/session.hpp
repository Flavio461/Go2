#ifndef SESSION_HPP
#define SESSION_HPP

#include "../utils/models/car.hpp"
#include "../utils/models/driver.hpp"
#include "../utils/route.hpp"
#include "../utils/data_base/dataBaseAPI.hpp"
#include "../utils/data_base/SHA256.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

class session {
private:
    route *email, *password, *confirmPassword = nullptr, *name = nullptr, *phone = nullptr;
    route *registerDriver = nullptr, *registerUser = nullptr;
    route *loginDriver = nullptr, *loginUser = nullptr;
    route *registerRoutine = nullptr, *loginRoutine = nullptr;
    dataBase *db = new dataBase();
public:
    session();
    void assemblyRegisterDriver(),
    assemblyRegisterUser(),
    assemblyLoginDriver(),
    assemblyLoginUser();
    route *getRegisterRoutine();
    route *getLoginRoutine();
};

#endif