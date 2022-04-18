#include "../include/Package.h"
#include "iostream"
using namespace std;


Package::Package(unsigned int id, unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration) : id(id), volume(volume),
    weight(weight), reward(reward), duration(duration){}

Package::~Package() = default;

unsigned int Package::getID() const {
    return this->id;
}

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

unsigned int Package::getDaysPast() const {
    return this->daysPast;
}

void Package::increaseDaysPast() {
    daysPast++;
}

bool Package::operator==(const Package &p) const {
    return volume == p.getVolume() && weight == p.getWeight() && reward == p.getReward() && duration == p.getDuration() && assigned == p.getAssignedValue();
}

ostream &operator<<(ostream &os, const Package &o) {
    os << o.getVolume() << " " << o.getWeight() << " " << o.getReward() << " " << o.getDuration();
    return os;
}

