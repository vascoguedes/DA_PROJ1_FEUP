#include "../include/Courier.h"
using namespace std;

Courier::Courier(unsigned int maxVolume, unsigned int maxWeight, unsigned int cost) : maxVolume(maxVolume), maxWeight(maxWeight), cost(cost){}

Courier::~Courier() = default;

unsigned int Courier::getMaxVolume() {
    return this->maxVolume;
}

unsigned int Courier::getMaxWeight() {
    return this->maxWeight;
}

unsigned int Courier::getCost() {
    return this->cost;
}


