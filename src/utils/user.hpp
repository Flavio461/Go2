#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class user {
protected:   
    int id;
    wchar_t *name, *email, *phone, *password;
public:
    user(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
    ~user();
    void setName(const wchar_t*);
    void setEmail(const wchar_t*);
    void setPhone(const wchar_t*);
    void setPassword(const wchar_t*);
    int getId();
    wchar_t* getName();
    wchar_t* getEmail();
    wchar_t* getPhone();
    wchar_t* getPassword();
    virtual std::wostream& getOutstreamBuffer(std::wostream&) const;
    friend std::wostream& operator<<(std::wostream&, const user&); //Acessa os membros privados da classe
};

#endif