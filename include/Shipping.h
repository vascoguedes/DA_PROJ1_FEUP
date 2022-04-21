
#ifndef DA_PROJ1_FEUP_SHIPPING_H
#define DA_PROJ1_FEUP_SHIPPING_H

#include <vector>
#include "Package.h"
#include <algorithm>

using namespace std;

/**
 * This class englobes what each Courier is shipping
 */
class Shipping {
    unsigned id;
    unsigned maxVolume;
    unsigned currentVolume;
    unsigned maxWeight;
    unsigned currentWeight;
    unsigned cost;
    vector <Package> packages;
    int profit;
    bool is_full;

public:

    /**
     * @brief Class constructor with 4 unsigned parameters
     * @param id Shipping id
     * @param maxVolume Shipping maximum volume supported
     * @param maxWeight Shipping maximum weight supported
     * @param cost Shipping cost to transport
     */
    Shipping(unsigned id, unsigned maxVolume, unsigned maxWeight, unsigned cost);

    /**
     * @brief Returns Shipping id
     * @return id parameter
     */
    unsigned getID() const;

    /**
     * @brief Returns Shipping cost to ship
     * @return cost parameter
     */
    unsigned getCost() const;

    /**
     * @brief Returns Shipping maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxVolume() const;

    /**
     * @brief Returns Shipping current volume supported
     * @return currentVolume parameter
     */
    unsigned getCurrentVolume() const;

    /**
     * @brief Returns Shipping maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxWeight() const;

    /**
     * @brief Returns Shipping current weight supported
     * @return currentWeight parameter
     */
    unsigned getCurrentWeight() const;

    /**
     * @brief Returns Shipping size
     * @return packages parameter size
     */
    unsigned getShippingSize() const;

    /**
     * @brief Returns Shipping profit
     * @return profit parameter
     */
    int getProfit() const;

    /**
     * @brief Sets Shipping currentVolume
     * @param volume Value to be added to Shipping currentVolume
     */
    void setCurrentVolume(unsigned volume);

    /**
     * @brief Sets Shipping currentWeight
     * @param weight Value to be added to Shipping currentWeight
     */
    void setCurrentWeight(unsigned weight);

    /**
     * @brief Sets Shipping profit
     * @param value Value to be added to Shipping profit
     */
    void setProfit(int value);

    /**
     * @brief Adds a package to packages
     * @param package Package object passed by reference
     */
    void pushPackage(Package& package);

    /**
     * @brief Sorts Packages by ID
     */
    void sortPackages();

    /**
     * @brief Returns Shipping packages
     * @return packages parameter
     */
    vector<Package> getPackages() const;

    /**
     * @brief Returns Shipping packages ids
     * @return packages parameter objects ids
     */
    vector<unsigned> getPackagesID() const;

    /**
     * Operator to print Shipping object in the correct format
     * @param os stream where Shipping will be printed
     * @param p Shipping object passed by reference
     * @return ostream with Shipping printed
     */
    friend std::ostream& operator<<(std::ostream& os, const Shipping &o);

};

#endif //DA_PROJ1_FEUP_SHIPPING_H
