#ifndef ROUTE_PATH_HPP
#define ROUTE_PATH_HPP

#include "route.hpp"

typedef struct routeList_t {
    route* data;
    routeList_t* next;
} routeList;

class routePath {
private:
    routeList *list;
public:
    routePath(route*);
    routePath();
    ~routePath();
    route* getNextRoute();
    routeList* getList();
    void addRoute(route*);
    friend std::wostream& operator<<(std::wostream&, const routePath&);
};

#endif