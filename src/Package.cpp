#include "../include/Package.h"

using namespace std;


Package::Package(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration) : volume(volume),
    weight(weight), reward(reward), duration(duration){}

Package::~Package() = default;

unsigned int Package::getVolume() {
    return this->volume;
}

unsigned int Package::getWeight() {
    return this->weight;
}

unsigned int Package::getReward() {
    return this->reward;
}

unsigned int Package::getDuration() {
    return this->duration;
}

