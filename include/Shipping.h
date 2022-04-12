
#ifndef DA_PROJ1_FEUP_SHIPPING_H
#define DA_PROJ1_FEUP_SHIPPING_H

#include <vector>
#include "Package.h"

using namespace std;

/**
 * This class englobes what each Courier is shipping
 */
class Shipping {
    unsigned maxVolume;
    unsigned currentVolume;
    unsigned maxWeight;
    unsigned currentWeight;
    vector <Package> package;
    int profit;
    bool is_full;

public:
    Shipping(unsigned maxVolume, unsigned maxWeight, unsigned cost);
    unsigned getMaxVolume() const;
    unsigned getCurrentVolume() const;
    unsigned getMaxWeight() const;
    unsigned getCurrentWeight() const;
    unsigned getShippingSize() const;
    int getProfit() const;
    void setCurrentVolume(unsigned volume);
    void setCurrentWeight(unsigned weight);
    void setProfit(int value);
    bool isFull() const;
    bool canFit(const Package& Package) const;

    void pushPackage(Package& package);
    void removePackage(Package& aPackage);
    vector<Package>& getPackages();
    void cleanPackage();
    bool aTenthFree();
};

#endif //DA_PROJ1_FEUP_SHIPPING_H
