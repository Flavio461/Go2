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
    db->writeUser(new user(L"Lucasa", L"Flavio@gmail", L"123456"), sha256("123456"));
    db->writeUser(new user(L"Pereira", L"Pereira@gmail", L"123456"), sha256("123456"));
    db->writeUser(new user(L"Lucas", L"Lucas@gmail", L"123456"), sha256("123456"));

    vector <user*> users = db->readUsers();
    for (auto u : users) {
        wcout << *u << endl;
    }

    db->writeDriver(new driver(L"Lucasa", L"Flavio@gmail", L"123456", L"123456", new car(L"Uno", L"ABC-1234")), sha256("123456"));
    db->writeDriver(new driver(L"Pereira", L"Pereira@gmail", L"123456", L"123456", new car(L"Uno", L"ABC-1234")), sha256("123456"));
    db->writeDriver(new driver(L"Lucas", L"Lucas@gmail", L"123456", L"123456", new car(L"Uno", L"ABC-1234")), sha256("123456"));
    vector <user*> drivers = db->readDrivers();
    
    for (auto d : drivers) {
        wcout << *d << endl;
    }

    session *sh = new session();
    routeHandler *rh = new routeHandler((
    new route(L"Menu principal"))
        ->addRoute(sh->getRegisterRoutine())
        ->addRoute(sh->getLoginRoutine())
    );

    rh->start();

    
    return 0;
}