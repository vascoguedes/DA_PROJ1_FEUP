//
// Created by arooz on 30/03/2022.
//

#ifndef DA_PROJ1_FEUP_COURIER_H
#define DA_PROJ1_FEUP_COURIER_H

#include "Shipping.h"

class Courier {
    unsigned id;
    unsigned maxVolume;
    unsigned maxWeight;
    unsigned cost;
public:
    /**
     * @brief Class constructor with 3 unsigned objects
     * @param maxVolume Courier maximum volume supported
     * @param maxWeight Courier maximum weight supported
     * @param cost Courier cost to transport
     */
    Courier(unsigned id, unsigned maxVolume, unsigned maxWeight, unsigned cost);

    /**
     * @brief Class destructor to clear the object in memory
     */
    ~Courier();

    /**
     * Returns Courier id
     * @return id parameter
     */
    unsigned getID() const;

    /**
     * Returns Courier maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxVolume() const;
    /**
     * Returns Courier maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxWeight() const;
    /**
     * Returns Courier cost to ship
     * @return cost parameter
     */
    unsigned getCost() const;

    friend std::ostream& operator<<(std::ostream& os, const Courier &o);
};


#endif //DA_PROJ1_FEUP_COURIER_H
