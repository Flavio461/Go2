#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <sstream>
#include <unordered_map>

class route {
private:
    route** nextRoutes;
    std::wstring name;
    bool autoReturn;
    size_t size;
    std::unordered_map<std::string, std::wstring> *payload;
    bool(*validateInput)(std::wstring const&);
    bool (*execute)(route*, bool(*)(std::wstring const&));
public:
    route(std::wstring, std::unordered_map<std::string, std::wstring>* = nullptr, bool (*)(route*, bool(*)(std::wstring const&)) = nullptr, bool = false, bool(*)(std::wstring const&) = nullptr);
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
    friend std::wostream& operator<<(std::wostream&, const route&);
};

#endif