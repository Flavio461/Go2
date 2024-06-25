#include <iostream>
#include <locale>
#include <windows.h>

#include "utils/models/car.hpp"
#include "utils/models/driver.hpp"
#include "utils/user.hpp"
#include "utils/route.hpp"
#include "utils/routeHandler.hpp"
#include "routes/session.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL, "Portuguese");
    session *sh = new session();
    routeHandler *rh = new routeHandler((
    new route(L"Menu principal"))
        ->addRoute(sh->getRegisterRoutine())
        ->addRoute(sh->getLoginRoutine())
    );
    rh->start();
    return 0;
}