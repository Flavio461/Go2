#include <iostream>
#include <locale>
#include <windows.h>

#include "utils/models/car.hpp"
#include "utils/models/driver.hpp"
#include "utils/models/user.hpp"
#include "utils/route.hpp"
#include "utils/routeHandler.hpp"
#include "routes/session.hpp"
#include "utils/data_base/dataBaseAPI.hpp"
#include "utils/data_base/SHA256.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL, "Portuguese");

    dataBase *db = new dataBase();
    session *sh = new session();
    routeHandler *rh = new routeHandler((
    new route(L"Menu principal"))
        ->addRoute(
            new route(L"Mostrar motoristas disponiveis", nullptr, [](route* r, bool(*f)(std::wstring const&)) {
                vector<user*> drivers = r->getDb()->readDrivers();
                for (auto d : drivers) {
                    if (((driver*)d)->isAvaliable()) {
                        wcout << *(driver*)d << endl;
                    }
                }
                return true;
            }, true, nullptr, db)
        )
        ->addRoute(
            new route(L"Mostrar usuarios", nullptr, [](route* r, bool(*f)(std::wstring const&)) {
                vector<user*> users = r->getDb()->readUsers();
                for (auto u : users) {
                    wcout << *u << endl;
                }
                return true;
            }, true, nullptr, db)
        )
        ->addRoute(
            new route(L"Escolher viagem", nullptr, [](route* r, bool(*f)(std::wstring const&)) {
                wcout << L"Digite a distância: ";
                double distance;
                wcin >> distance;
                wcout << L"Digite o peso de carga: ";
                double weight;
                wcin >> weight;
                wcout << L"Digite a quantidade de passageiros: ";
                int passengers;
                wcin >> passengers;
                vector<user*> drivers = r->getDb()->readDrivers();
                wcout << L"Digite o id do motorista: ";
                int id;
                wcin >> id;
                driver* chosen = nullptr;
                for (auto d : drivers) {
                    if (d->getId() == id) {
                        chosen = (driver*)d;
                        break;
                    }
                }
                if (chosen == nullptr) {
                    wcout << L"Motorista não encontrado" << endl;
                    return true;
                }
                if (!chosen->isAvaliable()) {
                    wcout << L"Motorista não está disponível" << endl;
                    return true;
                }
                wcout << L"Motorista escolhido: " << *chosen << endl;
                wcout << L"Valor da viagem: " << passengers*2*distance + weight*.2*distance << L"R$" endl;
                return true;
            }, true, nullptr, db)
        )
    );

    rh->start();

    return 0;
}