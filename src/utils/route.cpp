#include "route.hpp"
#include <iostream>

route::route(std::wstring name, std::unordered_map<std::string, std::wstring> *payload, bool (*execute)(route*, bool(*)(std::wstring const&)), bool autoReturn, bool(*validateInput)(std::wstring const&)): name(name), size(), payload(payload), execute(execute), autoReturn(autoReturn), validateInput(validateInput) {}
route::route(std::wstring name, std::unordered_map<std::string, std::wstring> *payload, bool (*execute)(route*, bool(*)(std::wstring const&)), bool autoReturn, bool(*validateInput)(std::wstring const&), dataBase *db): name(name), size(), payload(payload), execute(execute), autoReturn(autoReturn), validateInput(validateInput), db(db) {}
route::~route() {delete[] nextRoutes; if(payload!=nullptr) delete payload;}
route* route::addRoute(route* r) {
    route** newRoutes = new route*[size+1];
    for(size_t i = 0; i < size; i++) {
        newRoutes[i] = nextRoutes[i];
    }
    newRoutes[size] = r;
    if (size > 0) delete[] nextRoutes;
    nextRoutes = newRoutes;
    size++;
    return this;
}
route* route::removeRoute(size_t i) {
    if(i>size || i<0) return nullptr;
    route** newRoutes = new route*[size-1];
    for(size_t j = 0, delta=0; j < size-1; j++) {
        if(j == i) delta++;
        newRoutes[j] = nextRoutes[j+delta];
    }
    delete[] nextRoutes;
    nextRoutes = newRoutes;
    size--;
    return newRoutes[i];
}
void route::setPayload(std::unordered_map<std::string, std::wstring> *p) {
    if(payload!=nullptr) delete payload;
    payload = p;
}
void route::setName(std::wstring n) {
    name = n;
}
void route::setFunction(bool (*f)(route*, bool(*)(std::wstring const&))) {
    execute = f;
}
route* route::getRoute(size_t i) {
    if(i>size-1) return nullptr;
    return nextRoutes[i];
}
bool (*route::getFunction())(route*, bool(*)(std::wstring const&)) {
    return execute;
}
bool (*route::getValidateInput())(std::wstring const&) {
    return validateInput;
}
void route::setValidateInput(bool(*v)(std::wstring const&)) {
    validateInput = v;
}
size_t route::getSize() {
    return size;
}
std::unordered_map<std::string, std::wstring>* route::getPayload() {
    return payload;
}
void route::showRoutes() {
    for(size_t i = 0; i < size; i++) {
        std::wcout << i+1 << " - " << *nextRoutes[i] << std::endl;
    }
}
bool route::isAutoReturn() {
    return autoReturn;
}
dataBase* route::getDb() {
    return db;
}
std::wostream& operator<<(std::wostream& out, const route& r) {
    out << r.name;
    return out;
}