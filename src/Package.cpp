#include "../include/Package.h"
#include "iostream"
using namespace std;


Package::Package(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration) : volume(volume),
    weight(weight), reward(reward), duration(duration){}

Package::~Package() = default;

unsigned int Package::getVolume() const {
    return this->volume;
}

unsigned int Package::getWeight() const {
    return this->weight;
}

unsigned int Package::getReward() const {
    return this->reward;
}

unsigned int Package::getDuration() const {
    return this->duration;
}

bool Package::getAssignedValue() const {
    return assigned;
}

void Package::setAssignedValue(bool value) {
    assigned = value;
}

bool Package::operator==(const Package &p) const {
    return volume == p.getVolume() && weight == p.getWeight() && reward == p.getReward() && duration == p.getDuration() && assigned == p.getAssignedValue();
}

