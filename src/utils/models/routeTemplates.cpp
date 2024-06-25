#include "routeTemplates.hpp"
#include <string>
#include "../data_base/SHA256.hpp"

route *inputTextRoute(std::wstring name, std::string key, std::wstring displayText = L"", bool(*validateInput)(std::wstring const&)) {
    std::unordered_map<std::string, std::wstring> *payload = new std::unordered_map<std::string, std::wstring>{{"displayText", displayText}, {key, L""}};
    return new route(name, payload, [](route *r, bool(*verification)(std::wstring const&)) -> bool {
        std::wcout << r->getPayload()->at("displayText") << std::endl;
        std::wstring input;
        std::getline(std::wcin, input);
        if (verification==nullptr) {
            for (auto o : *r->getPayload()) 
                if (o.first != "displayText") {
                    r->getPayload()->operator[](o.first) = input;
                    break;
                }
            return true;
        }
        if(verification(input)) {
            for (auto o : *r->getPayload())  {
                if (o.first != "displayText") r->getPayload()->operator[](o.first) = input;
                break;
            }
            return true;
        }
        std::wcout << L"Entrada inválida" << std::endl;
        return false;
    }, true, validateInput);
}