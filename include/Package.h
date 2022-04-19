//
// Created by arooz on 30/03/2022.
//

#ifndef DA_PROJ1_FEUP_PACKAGE_H
#define DA_PROJ1_FEUP_PACKAGE_H


#include <ostream>

class Package {
    unsigned id;
    static unsigned ID;
    unsigned volume;
    unsigned weight;
    unsigned reward;
    unsigned duration;
    bool assigned;
    unsigned daysPast = 0;

public:

    /**
     * @brief Class constructor with 4 unsigned parameters
     * @param volume Package volume
     * @param weight Package weight
     * @param reward Package reward value
     * @param duration Package delivery time duration
     */
    Package(unsigned volume, unsigned weight, unsigned reward, unsigned duration);

    /**
     * @brief Class destructor to clear the object in memory
     */
    ~Package();

    /**
     * @brief Returns Package id
     * @return id parameter
     */
    unsigned getID() const;

    /**
     * @brief Returns Package volume
     * @return volume parameter
     */
    unsigned getVolume() const;

    /**
     * @brief Returns Package weight
     * @return weight parameter
     */
    unsigned getWeight() const;

    /**
     * @brief Returns Package reward
     * @return reward parameter
     */
    unsigned getReward() const;

    /**
     * @brief Returns Package duration
     * @return duration parameter
     */
    unsigned getDuration() const;

    /**
     * @brief Returns Package assignedValue
     * @return assignedValue parameter
     */
    bool getAssignedValue() const;

    /**
     * @brief Sets Package assignedValue
     * @param value Bool to be assigned to assignedValue
     */
    void setAssignedValue(bool value);

    /**
     * @brief Returns Package daysPast
     * @return daysPast parameter
     */
    unsigned getDaysPast() const;

    /**
     * @brief Increases Package daysPast by one
     */
    void increaseDaysPast();

    /**
     * Operator to print Package object in the correct format
     * @param os stream where Package will be printed
     * @param p Package object passed by reference
     * @return ostream with Package printed
     */
    bool operator==(const Package& p) const;
    friend std::ostream& operator<<(std::ostream& os, const Package &o);
};

#endif //DA_PROJ1_FEUP_PACKAGE_H
