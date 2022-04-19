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
     * @brief Class constructor with 4 unsigned parameters
     * @param id Shipping id
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
     * @brief Returns Courier id
     * @return id parameter
     */
    unsigned getID() const;

    /**
     * @brief Returns Courier maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxVolume() const;

    /**
     * @brief Returns Courier maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxWeight() const;

    /**
     * @brief Returns Courier cost to ship
     * @return cost parameter
     */
    unsigned getCost() const;

    /**
     * Operator to print Courier object in the correct format
     * @param os stream where Courier will be printed
     * @param p Courier object passed by reference
     * @return ostream with Courier printed
     */
    friend std::ostream& operator<<(std::ostream& os, const Courier &o);
};


#endif //DA_PROJ1_FEUP_COURIER_H
