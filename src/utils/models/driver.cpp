#include "driver.hpp"

driver::driver(const wchar_t* name, const wchar_t* email, const wchar_t* phone, const wchar_t* cnh, car* car, bool avaliable) : user(name, email, phone), cnh(wcsdup(cnh)), c(car), avaliable(avaliable) {}
driver::~driver() {delete c;}
void driver::setCar(car* c) {delete this->c; this->c = c;}
void driver::setCnh(const wchar_t* c) {free(cnh); this->cnh = wcsdup(c);}
car* driver::getCar() {return c;}
wchar_t* driver::getCnh() {return cnh;}
bool driver::isAvaliable() {return avaliable;}
std::wostream& driver::getOutstreamBuffer(std::wostream& out) const {
    out << "ID: "  << id << "\n" << "Nome: " << name << "\n" << "Email: " << email << "\n" << "Telefone: " << phone << "\n" << "CNH: " << cnh << "\n";
    c->getOutstreamBuffer(out);
    return out;
}
