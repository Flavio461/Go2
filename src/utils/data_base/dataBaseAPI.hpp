#ifndef DATA_BASE_API_H
#define DATA_BASE_API_H

#define USER_FILE_PATH "data/users.bin"
#define DRIVER_FILE_PATH "data/drivers.bin"

#include <fstream>
#include "../models/user.hpp"
#include "../models/car.hpp"
#include "../models/driver.hpp"
#include <vector>

class dataBase {
    private:
    std::fstream userFile;
    std::fstream driverFile;
    public:
    dataBase();
    ~dataBase();
    void writeUser(user*, std::string);
    void writeDriver(driver*, std::string);
    std::vector<user*> readUsers();
    std::vector<user*> readDrivers();
    user* getUser(std::wstring, std::string);
    driver* getDriver(std::wstring, std::string);
};

#endif