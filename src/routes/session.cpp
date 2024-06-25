#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "session.hpp"
#include "../utils/models/routeTemplates.hpp"

session::session() {
    email = inputTextRoute(L"Email", "email", L"Digite seu email: ", [](std::wstring const& input) -> bool {
        return input.find(L"@") != std::wstring::npos;
    });
    password = inputTextRoute(L"Senha", "password", L"Digite sua senha (pelo menos 8 caracteres): ", [](std::wstring const& input) -> bool {
        return input.size() >= 8;
    });
    this->db = new dataBase();
}

void session::assemblyRegisterDriver() {
    if (name == nullptr) 
        name = inputTextRoute(L"Nome", "name", L"Digite seu nome: ");
    if (phone == nullptr)
        phone = inputTextRoute(L"Telefone", "phone", L"Digite seu telefone: ");
    if(confirmPassword == nullptr) 
        confirmPassword = inputTextRoute(L"Confirmar senha", "confirm-password", L"Digite sua senha (pelo menos 8 caracteres): ", [](std::wstring const& input) -> bool {
            return input.size() >= 8;
    });
    registerDriver = (new route(L"Cadastrar motorista", new std::unordered_map<std::string, std::wstring>{
        {"type", L"driver"},
        {"name", L""},
        {"email", L""},
        {"password", L""},
        {"confirm-password", L""},
        {"phone", L""},
        {"cnh", L""},
        {"model", L""},
        {"plate", L""}},
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (size_t i = 0; i < r->getSize() - 1; i++) {
                if (r->getRoute(i)->getPayload() != nullptr &&
                    r->getRoute(i)->getPayload()->size() > 0) {
                    for (auto o : *r->getRoute(i)->getPayload()) {
                        if (o.first == "displayText") continue;
                        r->getPayload()->operator[](o.first) =
                            o.second;
                    }
                }
            }
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            r->getRoute(8)->setPayload(new std::unordered_map<std::string, std::wstring>(*r->getPayload()));

            return true;
        }))
    ->addRoute(name)
    ->addRoute(email)
    ->addRoute(password)
    ->addRoute(confirmPassword)
    ->addRoute(phone)
    ->addRoute(inputTextRoute(L"CNH", "cnh", L"Digite sua CNH: ", [](std::wstring const& input) -> bool {
        bool isValid = false;
        std::wstring cnh = input;
        wchar_t firstChar = cnh[0];
        if (cnh.size() == 11 && cnh != std::wstring(11, '1')) {
            int dsc = 0;
            int v = 0;
            for (size_t i = 0, j = 9; i < 9; i++, j--) {
                v += (std::stoi(cnh.substr(i, 1)) * j);
            }

            int vl1 = v % 11;
            if (vl1 >= 10) {
                vl1 = 0;
                dsc = 2;
            }
        
            v = 0;
            for (size_t i = 0, j = 1; i < 9; ++i, ++j) {
                v += (std::stoi(cnh.substr(i, 1)) * j);
            }

            int x = v % 11;
            int vl2 = (x >= 10) ? 0 : x - dsc;

            isValid = std::to_wstring(vl1) + std::to_wstring(vl2) == cnh.substr(cnh.size() - 2, 2);
        }
        return isValid;
    }))
    ->addRoute(inputTextRoute(L"Modelo do carro", "model", L"Digite o modelo do seu carro: "))
    ->addRoute(inputTextRoute(L"Placa do carro", "plate", L"Digite a placa do seu carro: ", [](std::wstring const& input) -> bool {
        bool isValid = false;
        std::wstring plate = input;
        plate.erase(std::remove_if(plate.begin(), plate.end(), ::isspace), plate.end());
        if (plate.size() == 7) {
            isValid = std::isalpha(plate[0]) && std::isalpha(plate[1]) && std::isalpha(plate[2]) && std::isdigit(plate[3]) && std::isalpha(plate[4]) && std::isdigit(plate[5]) && std::isdigit(plate[6]);
        }
        return isValid;
    }))
    ->addRoute(new route(L"Finalizar cadastro", new std::unordered_map<std::string, std::wstring>{{"displayText", L"Finalizar cadastro"}}, 
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            if (r->getPayload() == nullptr ||
                r->getPayload()->at("name").empty() ||
                r->getPayload()->at("email").empty() ||
                r->getPayload()->at("password").empty() ||
                r->getPayload()->at("confirm-password").empty() ||
                r->getPayload()->at("phone").empty() ||
                r->getPayload()->at("cnh").empty() ||
                r->getPayload()->at("model").empty() ||
                r->getPayload()->at("plate").empty()) {
                std::wcout << "Preencha todos os campos!" << std::endl;
                return false;
            }

            if(r->getPayload()->at("password") != r->getPayload()->at("confirm-password")) {
                std::wcout << "As senhas não são iguais!" << std::endl;
                return false;
            }

            car *c = new car(
                r->getPayload()->at("modelo").c_str(),
                r->getPayload()->at("placa").c_str());

            driver *d = new driver(
                r->getPayload()->at("nome").c_str(),
                r->getPayload()->at("email").c_str(),
                L"", r->getPayload()->at("cnh").c_str(),
                c);
            std::wcout << *d;

            r->getDb()->writeDriver(d, sha256(utf8_encode(r->getPayload()->at("password").c_str())));
            return true;
        }, true, nullptr, this->db
    ));
}

void session::assemblyRegisterUser() {
    if (name == nullptr) 
        name = inputTextRoute(L"Nome", "name", L"Digite seu nome: ");
    if (phone == nullptr)
        phone = inputTextRoute(L"Telefone", "phone", L"Digite seu telefone: ");
    if(confirmPassword == nullptr) 
        confirmPassword = inputTextRoute(L"Confirmar senha", "confirm-password", L"Digite sua senha (pelo menos 8 caracteres): ", [](std::wstring const& input) -> bool {
        return input.size() >= 8;
    });
    registerUser = (new route(L"Cadastrar usuário", new std::unordered_map<std::string, std::wstring>{

        {"type", L"user"},
        {"name", L""},
        {"email", L""},
        {"password", L""},
        {"confirm-password", L""},
        {"phone", L""}},
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (size_t i = 0; i < r->getSize() - 1; i++) {
                if (r->getRoute(i)->getPayload() != nullptr &&
                    r->getRoute(i)->getPayload()->size() > 0) {
                    for (auto o : *r->getRoute(i)->getPayload()) {
                        if (o.first == "displayText") continue;
                        r->getPayload()->operator[](o.first) =
                            o.second;
                    }
                }
            }
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            r->getRoute(5)->setPayload(
                new std::unordered_map<std::string, std::wstring>(
                    *r->getPayload()));

            return true;
        }))
    ->addRoute(name)
    ->addRoute(email)
    ->addRoute(password)
    ->addRoute(confirmPassword)
    ->addRoute(phone)
    ->addRoute(new route(L"Finalizar cadastro", new std::unordered_map<std::string, std::wstring>{{"displayText", L"Finalizar cadastro"}}, 
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            r->getDb()->writeUser(new user(L"Lucasa", L"Flavio@gmail.com", L"123456"), sha256("12345678"));
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }

            if (r->getPayload() == nullptr ||
                r->getPayload()->at("name").empty() ||
                r->getPayload()->at("email").empty() ||
                r->getPayload()->at("password").empty() ||
                r->getPayload()->at("confirm-password").empty() ||
                r->getPayload()->at("phone").empty()) {
                std::wcout << "Preencha todos os campos!" << std::endl;
                return false;
            }

            if(r->getPayload()->at("password") != r->getPayload()->at("confirm-password")) {
                std::wcout << "As senhas não são iguais!" << std::endl;
                return false;
            }

            user *u = new user(
                r->getPayload()->at("name").c_str(),
                r->getPayload()->at("email").c_str(),
                r->getPayload()->at("phone").c_str());
            std::wcout << *u << std::endl;
            r->getDb()->writeUser(u, sha256(utf8_encode(r->getPayload()->at("password").c_str())));

            return true;
        }, true, nullptr, this->db
    ));
}

void session::assemblyLoginDriver() {
    loginDriver = (new route(L"Login motorista", new std::unordered_map<std::string, std::wstring>{
        {"type", L"driver"},
        {"email", L""},
        {"password", L""}},
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (size_t i = 0; i < r->getSize() - 1; i++) {
                if (r->getRoute(i)->getPayload() != nullptr &&
                    r->getRoute(i)->getPayload()->size() > 0) {
                    for (auto o : *r->getRoute(i)->getPayload()) {
                        if (o.first == "displayText") continue;
                        r->getPayload()->operator[](o.first) =
                            o.second;
                    }
                }
            } 
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            r->getRoute(2)->setPayload(
                new std::unordered_map<std::string, std::wstring>(
                    *r->getPayload()));

            return true;
        }))
    ->addRoute(email)
    ->addRoute(password)
    ->addRoute(new route(L"Finalizar login", new std::unordered_map<std::string, std::wstring>{{"displayText", L"Finalizar login"}}, 
    [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            if (r->getPayload() == nullptr ||
                r->getPayload()->at("email").empty() ||
                r->getPayload()->at("password").empty()) {
                std::wcout << L"Preencha todos os campos!" << std::endl;
                return false;
            }

            driver* d = r->getDb()->getDriver(r->getPayload()->at("email").c_str(), sha256(utf8_encode(r->getPayload()->at("password").c_str())));
            if (d == nullptr) {
                std::wcout << L"Motorista não encontrado!" << std::endl;
                return false;
            }
            return true;
        }, true, nullptr, this->db
    ));
}

void session::assemblyLoginUser() {
    loginUser = (new route(L"Login usuário", new std::unordered_map<std::string, std::wstring>{
        {"type", L"user"},
        {"email", L""},
        {"password", L""}},
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (size_t i = 0; i < r->getSize() - 1; i++) {
                if (r->getRoute(i)->getPayload() != nullptr &&
                    r->getRoute(i)->getPayload()->size() > 0) {
                    for (auto o : *r->getRoute(i)->getPayload()) {
                        if (o.first == "displayText") continue;
                        r->getPayload()->operator[](o.first) =
                            o.second;
                    }
                }
            }
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            r->getRoute(2)->setPayload(
                new std::unordered_map<std::string, std::wstring>(
                    *r->getPayload()));

            return true;
        }))
    ->addRoute(email)
    ->addRoute(password)
    ->addRoute(new route(L"Finalizar login", new std::unordered_map<std::string, std::wstring>{{"displayText", L"Finalizar login"}}, 
        [](route *r, bool(*verification)(std::wstring const&)) -> bool {
            for (auto o : *r->getPayload()) {
                if (o.first == "password" || o.first == "confirm-password") {
                    std::wcout << o.first.c_str() << L": " << std::wstring(o.second.size(), L'•') << std::endl;
                    continue;
                }
                std::wcout << o.first.c_str() << L": " << o.second << std::endl;
            }
            if (r->getPayload() == nullptr ||
                r->getPayload()->at("email").empty() ||
                r->getPayload()->at("password").empty()) {
                std::wcout << L"Preencha todos os campos!" << std::endl;
                return false;
            }

            user* u = r->getDb()->getUser(r->getPayload()->at("email").c_str(), sha256(utf8_encode(r->getPayload()->at("password").c_str())));
            if (u == nullptr) {
                std::wcout << L"Usuário não encontrado!" << std::endl;
                return false;
            }

            std::wcout << *u << std::endl;
            return true;
        }, true, nullptr, this->db
    ));
}

route* session::getLoginRoutine() {
    if (loginRoutine != nullptr)
        return loginRoutine;
    if(loginDriver == nullptr)
        assemblyLoginDriver();
    if(loginUser == nullptr)
        assemblyLoginUser();
    loginRoutine = (new route(L"Login"))
    ->addRoute(loginDriver)
    ->addRoute(loginUser);
    return loginRoutine;
}

route* session::getRegisterRoutine() {
    if (registerRoutine != nullptr)
        return registerRoutine;
    if(registerDriver == nullptr)
        assemblyRegisterDriver();
    if(registerUser == nullptr)
        assemblyRegisterUser();
    registerRoutine = (new route(L"Registrar"))
    ->addRoute(registerDriver)
    ->addRoute(registerUser);
    return registerRoutine;
}