#ifdef __STDC_ALLOC_LIB__ //Verifica se o compilador suporta a biblioteca com a função wcsdup
#define __STDC_WANT_LIB_EXT2__ 1 //Define que a função wcsdup está disponível
#else
#define _POSIX_C_SOURCE 200809L //Usa a biblioteca POSIX para o wcsdup
#endif

#include <string.h>
#include "user.hpp"

user::user(const wchar_t* name, const wchar_t* email, const wchar_t* phone, int id) : name(wcsdup(name)), email(wcsdup(email)), phone(wcsdup(phone)), id(id) {
    if (id != -1) return;
    static int iid = 0;
    this->id = iid++;
}

user::~user() {free(this->name); free(this->email); free(this->phone);}
void user::setName(const wchar_t* name) {free(this->name); this->name = wcsdup(name);}
void user::setEmail(const wchar_t* email) {free(this->email); this->email = wcsdup(email);}
void user::setPhone(const wchar_t* phone) {free(this->phone); this->phone = wcsdup(phone);}
int user::getId() {return id;}
wchar_t* user::getName() {return name;}
wchar_t* user::getEmail() {return email;}
wchar_t* user::getPhone() {return phone;}
std::wostream& user::getOutstreamBuffer(std::wostream& out) const {return (out << "ID: " << id << "\n" << "Nome: " << name << "\n" << "Email: " << email << "\n" << "Telefone: " << phone);}

//Adiciona o operador de inserção para que seja possível imprimir o objeto
std::wostream& operator<<(std::wostream& out, const user& u) {
    return (u.getOutstreamBuffer(out));
}