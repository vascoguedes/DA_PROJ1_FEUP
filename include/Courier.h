//
// Created by arooz on 30/03/2022.
//

#ifndef DA_PROJ1_FEUP_COURIER_H
#define DA_PROJ1_FEUP_COURIER_H


class Courier {
    unsigned maxVolume;
    unsigned maxWeight;
    unsigned cost;
public:
    /**
     * Class constructor with 3 unsigned objects
     * @param maxVolume Courier maximum volume supported
     * @param maxWeight Courier maximum weight supported
     * @param cost Courier cost to transport
     */
    Courier(unsigned maxVolume, unsigned maxWeight, unsigned cost);

    /**
     * Class destructor to clear the object in memory
     */
    ~Courier();
    /**
     * Returns Courier maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxVolume();
    /**
     * Returns Courier maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxWeight();
    /**
     * Returns Courier cost to ship
     * @return cost parameter
     */
    unsigned getCost();
};


#endif //DA_PROJ1_FEUP_COURIER_H
