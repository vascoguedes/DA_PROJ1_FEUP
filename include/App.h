#ifndef DA_PROJ1_FEUP_APP_H
#define DA_PROJ1_FEUP_APP_H

#include "FileReader.h"
#include "Shipping.h"
#include "map"

class App{
private:
    FileReader fileReader;
    string filepath = "../dataFiles/";
    vector<Courier> couriers;
    vector<Package> packages;
    vector<Shipping> shipments;
    vector<Package> expressPackages;
public:

    /**
     * @brief Default Constructor
     */
    App();

    /**
     * Loads all storage files data into the program
     */
    void loadData();

    /**
     * Loads more packages into the program
     */
    void loadPackages(const string& fileName);
    /**
     *
     * @brief Prints to the console the vector of Couriers
     */
    void printCouriers();

    /**
     * @brief Prints to the console the vector of Packages
     */
    void printPackages();

    /**
     * @brief Prints to the console the vector of Shipments
     * @param scenery chooses the scenery to print
     */
    void printShipments(int scenery);

    /**
     * @brief Writes the Shipment vector to a file with the most adequate parameters according to the scenery
     * @param scenery chooses the scenery to write to a file
     */
    void writeShipments(int scenery);

    /**
     * @brief Sorts the Couriers according to a certain algorithm
     * @param sort_algorithm defines sorting algorithm
     */
    void sortCouriers(int sort_algorithm);

    /**
     * @brief Sorts the Packages according to a certain algorithm
     * @param sort_algorithm defines sorting algorithm
     */
    void sortPackages(int sort_algorithm);

    /**
     * @brief Sorts with a Knapsack algorithm a shipment vector that contains the packages in each courier
     * @return Amount of Couriers used for all packages
     */
    int scenery1();

    /**
     * @brief Fills the shipment vector with a Best-Fit algorithm
     */
    void bestFitAlgorithm();

    /**
     * @brief Fills the shipment vector with a 0-1 Knapsack algorithm
     */
    void knapSackAlgorithm();

    /**
     * @brief Sorts with a Knapsack or Best-Fit algorithm a shipment vector that contains the packages in each courier
     * @param knapsack If true, Knapsack algorithm will be used. If false, Best-Fit will be used
     * @return Profit of the shipment given by sortProfits() function
     */
    int scenery2(bool knapsack);

    /**
     * @brief Clears Shipment vector
     */
    void unloadShipments();

    /**
     * @brief Removes from the Shipment vector those who have negative profit
     * @return Profit of shipment
     */
    int sortProfits();

    /**
     * @brief Sorts package vector with an ascending duration and finds the average delivery time of each package that can be delivered on the current day from 9:00 to 17:00
     * @return Average delivery time of each package
     */
    int scenery3();
};

#endif //DA_PROJ1_FEUP_APP_H
