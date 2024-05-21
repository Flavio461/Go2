#include "car.hpp"

car::car(int id, const wchar_t* model, const wchar_t* plate) : id(id), model(wcsdup(model)), plate(wcsdup(plate)) {}
car::~car() {free(this->model); free(this->plate);}
void car::setModel(const wchar_t* model) {free(this->model); this->model = wcsdup(model);}
void car::setPlate(const wchar_t* plate) {free(this->plate); this->plate = wcsdup(plate);}
int car::getId() {return id;}
wchar_t* car::getModel() {return model;}
wchar_t* car::getPlate() {return plate;}
std::wostream& car::getOutstreamBuffer(std::wostream& out) const {
    return (out << "Carro " << "\n" <<  "id: " << id << "\n" << "Modelo: " << model << "\n" << "Placa: " << plate << "\n");
}

std::wostream& operator<<(std::wostream& out, const car& c) {
    return c.getOutstreamBuffer(out);
}