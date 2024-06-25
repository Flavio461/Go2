#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <sstream>
#include <unordered_map>
#include "../utils/data_base/dataBaseAPI.hpp"

class route {
private:
    route** nextRoutes;
    std::wstring name;
    bool autoReturn;
    size_t size;
    std::unordered_map<std::string, std::wstring> *payload;
    bool(*validateInput)(std::wstring const&);
    bool (*execute)(route*, bool(*)(std::wstring const&));
    dataBase *db;
public:
    route(std::wstring, std::unordered_map<std::string, std::wstring>* = nullptr, bool (*)(route*, bool(*)(std::wstring const&)) = nullptr, bool = false, bool(*)(std::wstring const&) = nullptr);
    route(std::wstring, std::unordered_map<std::string, std::wstring>*, bool (*)(route*, bool(*)(std::wstring const&)), bool, bool(*)(std::wstring const&), dataBase*);

    ~route();
    route* addRoute(route*);
    route* removeRoute(size_t);
    void setPayload(std::unordered_map<std::string, std::wstring>*);
    void setName(std::wstring);
    void setFunction(bool (*)(route*, bool(*)(std::wstring const&)));
    void setValidateInput(bool(*)(std::wstring const&));
    route* getRoute(size_t);
    bool(*getValidateInput())(std::wstring const&);
    bool (*getFunction()) (route*, bool(*)(std::wstring const&));
    size_t getSize();
    std::unordered_map<std::string, std::wstring>* getPayload();
    void showRoutes();
    bool isAutoReturn();
    dataBase* getDb();
    friend std::wostream& operator<<(std::wostream&, const route&);
};

#endif