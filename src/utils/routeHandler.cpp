#include "routeHandler.hpp"
#include "routePath.hpp"
#include <iostream>
#include <algorithm>

routeHandler::routeHandler(route* r) : root(r), path(new routePath()), current(r) {}
routeHandler::~routeHandler() {delete root;}
void routeHandler::showRoutes() {
    current->showRoutes();
    if(path->getList()!=nullptr) std::wcout << "0 - Voltar" << std::endl;
}
route* routeHandler::getRoute(size_t i) {
    if(i<0) return nullptr;
    if(i==0) {
        if(path==nullptr || path->getList()==nullptr) {
            std::wcout << L"Não é possível voltar!" << std::endl;
            return nullptr;
        }
        current = path->getNextRoute();
        if (current->getFunction()!=nullptr) while(!current->getFunction()(current, current->getValidateInput()?current->getValidateInput():[](std::wstring const&){return true;}) && current->getValidateInput()!=nullptr) {};
        return current;
    }
    if(i>current->getSize()) {
        std::wcout << L"Opção inválida!" << std::endl;
        return nullptr;
    }
    if(path==nullptr) path = new routePath(current);
    else path->addRoute(current);
    if(current->getRoute(i-1)!=nullptr) {
        current = current->getRoute(i-1);
        if (current->getFunction()!=nullptr) while(!current->getFunction()(current, current->getValidateInput()?current->getValidateInput():[](std::wstring const&){return true;}) && current->getValidateInput()!=nullptr) {};
        return current;
    }
    return nullptr;
}
std::wstring routeHandler::dispose() {
    if(current->isAutoReturn()) {
        getRoute(0);
        return L"0";
    }

    std::wcout << L"Caminho atual: " << *current << *path << std::endl;
    std::wcout << L"Escolha uma opção ou feche o programa (\"sair\"): " << std::endl;
    showRoutes();
    std::wstring userInput;
    bool validNumber = false;
    size_t n;
    do {
        getline(std::wcin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
        try {
            n = std::stoi(userInput);
            validNumber = true;
        } catch(std::invalid_argument) {
            n=-1;
            validNumber = false;
        }
    } while(userInput!=L"sair"&&(!validNumber||getRoute(n)==nullptr));
    return userInput;
}
void routeHandler::start() {
    while(dispose()!=L"sair") {}
}