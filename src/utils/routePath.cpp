#include "routePath.hpp"

routePath::routePath(route* r) : list(new routeList{r, nullptr}) {}
routePath::routePath() : list(nullptr) {}
routePath::~routePath() {
    routeList* nextList;
    while(this->list!=nullptr) {
        nextList = this->list->next;
        delete this->list;
        this->list = nextList;
    }
}
void routePath::addRoute(route* r) {
    this->list = new routeList{r, this->list};
}
route* routePath::getNextRoute() {
    route* r = this->list->data;
    routeList* nextList = this->list->next;
    delete this->list;
    this->list = nextList;
    return r;
}
routeList* routePath::getList() {
    return this->list;
}
std::wostream& operator<<(std::wostream& out, const routePath& rp) {
    if(&rp==nullptr) return out;
    routeList* current = rp.list;
    while(current!=nullptr) {
        out << " <- " << *current->data;
        current = current->next;
    }
    return out;
}