#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <sstream>
#include <unordered_map>

class route {
private:
    route** nextRoutes;
    std::wstring name;
    size_t size;
    std::unordered_map<std::string, std::wstring> *payload;
    void (*execute)(route*);
public:
    route(std::wstring, std::unordered_map<std::string, std::wstring>* = nullptr, void (*)(route*) = nullptr);
    ~route();
    route* addRoute(route*);
    route* removeRoute(size_t);
    void setPayload(std::unordered_map<std::string, std::wstring>*);
    void setName(std::wstring);
    void setFunction(void (*)(route*));
    route* getRoute(size_t);
    route* getParent();
    void (*getFunction()) (route*);
    size_t getSize();
    std::unordered_map<std::string, std::wstring>* getPayload();
    void showRoutes();
    friend std::wostream& operator<<(std::wostream&, const route&);
};


#endif