
#include "../include/Shipping.h"

Shipping::Shipping(unsigned int id, unsigned int maxVolume, unsigned int maxWeight, unsigned int cost) {
    this->id = id;
    this->maxWeight = maxWeight;
    this->maxVolume = maxVolume;
    currentWeight = 0;
    currentVolume = 0;
    this->cost = cost;
    profit = 0;
    profit -=(int)cost;
    is_full = false;
}

unsigned Shipping::getID() const {
    return id;
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

unsigned Shipping::getCost() const {
    return cost;
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
    setProfit((int)packag.getReward());

}

vector<Package> Shipping::getPackages() const {
    return packages;
}

bool Shipping::canFit(const Package& package1) const {
    return ((maxVolume - currentVolume) >= package1.getVolume()) && ((maxWeight - currentWeight) >= package1.getWeight());
}

void Shipping::removePackage(Package &aPackage) {
    for (int i = 0; i < packages.size(); ++i) {
        if (packages[i].getID() == aPackage.getID()) {
            packages.erase(packages.begin() + i);
            break;
        }
    }
    aPackage.setAssignedValue(false);
    setCurrentVolume(-aPackage.getVolume());
    setCurrentWeight(-aPackage.getWeight());
}

void Shipping::clearPackages() {
    packages = {};
    setCurrentVolume(-currentVolume);
    setCurrentWeight(-currentWeight);
}


vector<unsigned> Shipping::getPackagesID() const {
    vector<unsigned> ret;
    for(const auto& pack: packages) {
        ret.push_back(pack.getID());
    }
    return ret;
}


ostream &operator<<(ostream &os, const Shipping &o) {
    os <<"  ID: " << o.getID() <<" Volume: "<<o.getCurrentVolume()<<"/"<<o.getMaxVolume() <<" Weight: "<<o.getCurrentWeight() << "/" << o.getMaxWeight();
    return os;
}
