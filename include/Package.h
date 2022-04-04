//
// Created by arooz on 30/03/2022.
//

#ifndef DA_PROJ1_FEUP_PACKAGE_H
#define DA_PROJ1_FEUP_PACKAGE_H


class Package {
    unsigned volume;
    unsigned weight;
    unsigned reward;
    unsigned duration;
public:
    Package(unsigned volume, unsigned weight, unsigned reward, unsigned duration);
    ~Package();
    unsigned getVolume() const;
    unsigned getWeight() const;
    unsigned getReward() const;
    unsigned getDuration() const;
};


#endif //DA_PROJ1_FEUP_PACKAGE_H
