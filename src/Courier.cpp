#include <iosfwd>
#include <iostream>
#include "../include/Courier.h"
using namespace std;

Courier::Courier(unsigned int id, unsigned int maxVolume, unsigned int maxWeight, unsigned int cost) : id(id), maxVolume(maxVolume), maxWeight(maxWeight), cost(cost), shipping(Shipping(id, maxVolume, maxWeight, cost)) {}

Courier::~Courier() = default;

unsigned int Courier::getID() const {
    return this->id;
}

unsigned int Courier::getMaxVolume() const {
    return this->maxVolume;
}

unsigned int Courier::getMaxWeight() const {
    return this->maxWeight;
}

unsigned int Courier::getCost() const {
    return this->cost;
}

Shipping Courier::getShipping() const {
    return shipping;
}

ostream &operator<<(ostream &os, const Courier &o) {
    os << o.getMaxVolume() << " " << o.getMaxWeight() << " " << o.getCost() << endl;
    return os;
}


