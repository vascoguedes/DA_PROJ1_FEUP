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
     * Default Constructor
     */
    App();

    /**
     * Loads all storage files data into the program
     */
    void loadData();

    /**
     * Prints to the console the vector of Couriers
     */
    void printCouriers();

    /**
     * Prints to the console the vector of Packages
     */
    void printPackages();

    /**
     * Prints to the console the vector of Shipments
     * @param scenery chooses the scenery to print
     */
    void printShipments(int scenery);

    void writeShipments(int scenery);

    void writeExpressShipments();

    void printExpressShipments();

    /**
     * Sorts the Couriers according to a certain algorithm
     * @param sort_algorithm defines sorting algorithm
     */
    void sortCouriers(int sort_algorithm);

    /**
     * Sorts the Couriers according to a certain algorithm
     * @param sort_algorithm defines sorting algorithm
     */
    void sortPackages(int sort_algorithm);

    /**
     * Sorts with a Knapsack algorithm a shipment vector that contains the packages in each courier
     * @return Amount of Couriers used for all packages
     */
    int scenery1();

    /**
     * Sorts with a Knapsack or Best-Fit algorithm a shipment vector that contains the packages in each courier
     * @param knapsack If true, Knapsack algorithm will be used. If false, Best-Fit will be used
     * @return Profit of the shipment
     */
    int scenery2(bool knapsack);

    /**
     * TODO
     * @return TODO
     */
    void knapSackAlgorithm();

    /**
     * TODO
     * @return TODO
     */
    void bestFitAlgorithm();

    /**
     * Clears Shipment vector
     */
    void unloadShipments();

    /**
     * Removes from the Shipment vector those who have negative profit
     * @return Profit of shipment
     */
    int sortProfits();

    /**
     *
     * @return Average delivery time of each package
     */
    int scenery3();
};

#endif //DA_PROJ1_FEUP_APP_H
