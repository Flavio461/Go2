#ifndef ROUTE_HANDLER_HPP
#define ROUTE_HANDLER_HPP

#include "route.hpp"
#include "routePath.hpp"

class routeHandler {
private:
    route* root, *current;
    routePath* path;
public:
    routeHandler(route*);
    ~routeHandler();
    void showRoutes();
    route* getRoute(size_t);
    std::wstring dispose();
    void start();
};

#endif