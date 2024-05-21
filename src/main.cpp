#include <iostream>
#include "utils/car.hpp"
#include "utils/driver.hpp"
#include "utils/user.hpp"
#include "utils/route.hpp"
#include "utils/routeHandler.hpp"
#include <locale>
#include <windows.h>

using namespace std;

int a(int n = 0) {return ++n;}

int main() {
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL, "Portuguese");
    routeHandler *rh = new routeHandler((
    new route(L"Menu principal"))
        ->addRoute((new route(L"Criar conta motorista", new std::unordered_map<std::string, std::wstring>{{"tipo", L"motorista"}, {"nome", L""}, {"email", L""}, {"senha", L""}, {"cnh", L""}, {"modelo", L""}, {"placa", L""}},
            [](route* r) {
                for(size_t i = 0; i < r->getSize()-1; i++) {
                    if(r->getRoute(i)->getPayload()!=nullptr && r->getRoute(i)->getPayload()->size()>0) {
                        for(auto o: *r->getRoute(i)->getPayload()) {              
                            std::wcout << o.first.c_str() << L": " << o.second << std::endl;
                            r->getPayload()->operator[](o.first) = o.second;
                        }
                    }
                }
                r->getRoute(6)->setPayload(new std::unordered_map<std::string, std::wstring>(*r->getPayload()));
            }))
            ->addRoute(new route(L"Nome", nullptr, 
                [](route* r) {
                    std::wcout << "Digite seu nome: ";
                    std::wstring nome;
                    std::getline(std::wcin, nome);
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"nome", nome}});
                    else r->getPayload()->operator[]("nome") = nome;
                }))
            ->addRoute(new route(L"Email", nullptr, 
                [](route* r) {
                    std::wcout << "Digite seu email: ";
                    std::wstring email;
                    std::wcin >> email;
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"email", email}});
                    else r->getPayload()->operator[]("email") = email;
                }))
            ->addRoute(new route(L"Senha", nullptr, 
                [](route* r) {
                    std::wcout << "Digite sua Senha: ";
                    std::wstring senha;
                    std::wcin >> senha;
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"senha", senha}});
                    else r->getPayload()->operator[]("senha") = senha;
                }))
            ->addRoute(new route(L"CNH", nullptr, 
                [](route* r) {
                    std::wcout << "Digite sua CNH: ";
                    std::wstring cnh;
                    std::wcin >> cnh;
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"cnh", cnh}});
                    else r->getPayload()->operator[]("cnh") = cnh;
                }))
            ->addRoute(new route(L"Modelo", nullptr, 
                [](route* r) {
                    std::wcout << "Digite o modelo do seu carro: ";
                    std::wstring modelo;
                    std::wcin >> modelo;
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"modelo", modelo}});
                    else r->getPayload()->operator[]("modelo") = modelo;
                }))
            ->addRoute(new route(L"Placa", nullptr, 
                [](route* r) {
                    std::wcout << "Digite a placa do seu carro: ";
                    std::wstring placa;
                    std::wcin >> placa;
                    if (r->getPayload()==nullptr) r->setPayload(new std::unordered_map<std::string, std::wstring>{{"placa", placa}});
                    else r->getPayload()->operator[]("placa") = placa;
                }))
            ->addRoute(new route(L"Finalizar", nullptr, 
                [](route* r) {
                    if(r->getPayload()==nullptr) {
                        std::wcout << "Preencha todos os campos!" << std::endl;
                        return;
                    }
                    for(auto o: *r->getPayload())
                        std::wcout << o.first.c_str() << L": " << o.second << std::endl;
                    if(r->getPayload()->at("nome").empty() || r->getPayload()->at("email").empty() || r->getPayload()->at("senha").empty() || r->getPayload()->at("cnh").empty() || r->getPayload()->at("modelo").empty() || r->getPayload()->at("placa").empty()) {
                        std::wcout << "Preencha todos os campos!" << std::endl;
                        return;
                    }
                    car* c = new car(0, r->getPayload()->at("modelo").c_str(), r->getPayload()->at("placa").c_str());
                    driver* d = new driver(r->getPayload()->at("nome").c_str(), r->getPayload()->at("email").c_str(), L"", r->getPayload()->at("cnh").c_str(), r->getPayload()->at("senha").c_str(), c);
                    wcout << *d;
                })))
        ->addRoute((new route(L"Criar conta passageiro"))
            ->addRoute(new route(L"Senha")))
    );
    rh->start();
    return 0;
}