
#include <iostream>
#include <utility>
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
    if(currentVolume >= maxVolume || currentWeight >= maxWeight)
        return true;
    else return false;
}

unsigned Shipping::getShippingSize() const{
    return packages.size();
}

void Shipping::pushPackage( Package &packag) {
    packag.setAssignedValue(true);
    packages.push_back(packag);
    setCurrentVolume(packag.getVolume());
    setCurrentWeight(packag.getWeight());
}

vector<Package> Shipping::getPackages() const {
    return packages;
}

bool Shipping::canFit(const Package& package1) const {
    return ((maxVolume - currentVolume) >= package1.getVolume()) && ((maxWeight - currentWeight) >= package1.getWeight());
}

void Shipping::removePackage(Package &aPackage) {
    for (int i = 0; i < packages.size(); ++i) {
        if (packages[i].getVolume() == aPackage.getVolume() && packages[i].getWeight() == aPackage.getWeight() && packages[i].getReward() == aPackage.getReward() && packages[i].getDuration() == aPackage.getDuration() && packages[i].getAssignedValue() == aPackage.getAssignedValue()) {
            packages.erase(packages.begin() + i);
            break;
        }
    }
    aPackage.setAssignedValue(false);
    setCurrentVolume(-aPackage.getVolume());
    setCurrentWeight(-aPackage.getWeight());
}

void Shipping::cleanPackage() {
    packages = {};
    setCurrentVolume(-currentVolume);
    setCurrentWeight(-currentWeight);
}

bool Shipping::aTenthFree() {
    return (maxWeight + maxVolume) * 0 < (maxWeight + maxVolume - currentWeight - currentVolume);
}
