#ifndef ROUTE_TEMPLATES_HPP
#define ROUTE_TEMPLATES_HPP

#include "../route.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

route *inputTextRoute(std::wstring, std::string, std::wstring, bool(*)(std::wstring const&) = [](std::wstring const&){return true;});

#endif