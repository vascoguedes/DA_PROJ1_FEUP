
#include "../include/Shipping.h"

Shipping::Shipping(unsigned int maxVolume, unsigned int maxWeight, unsigned int cost) {
    this->maxWeight = maxWeight;
    this->maxVolume = maxVolume;
    currentWeight = 0;
    currentVolume = 0;
    profit = 0;
    profit -=(int)cost;
    is_full = false;
}

unsigned Shipping::getMaxVolume() const {
    return maxVolume;
}

unsigned Shipping::getCurrentVolume() const {
    return currentVolume;
}

unsigned Shipping::getMaxWeight() const {
    return maxWeight;
}

unsigned Shipping::getCurrentWeight() const {
    return currentWeight;
}

int Shipping::getProfit() const {
    return profit;
}

void Shipping::setCurrentVolume(unsigned int volume) {
    currentVolume += volume;
}

void Shipping::setCurrentWeight(unsigned int weight) {
    currentWeight += weight;
}

void Shipping::setProfit(int value) {
    profit += value;
}

bool Shipping::isFull() const {
    if(currentVolume == maxVolume || currentWeight == maxWeight)
        return true;
    else return false;
}

unsigned Shipping::getShippingSize() const{
    return package.size();
}

void Shipping::pushPackage(const Package& packag) {
    package.push_back(packag);
}

