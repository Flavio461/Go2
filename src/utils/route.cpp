#include "route.hpp"
#include <iostream>

route::route(std::wstring name, std::unordered_map<std::string, std::wstring> *payload, void (*execute)(route*)): name(name), size(), payload(payload), execute(execute) {}
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
void route::setFunction(void (*f)(route*)) {
    execute = f;
}
route* route::getRoute(size_t i) {
    if(i>size-1) return nullptr;
    return nextRoutes[i];
}
void (*route::getFunction())(route*) {
    return execute;
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
std::wostream& operator<<(std::wostream& out, const route& r) {
    out << r.name;
    return out;
}