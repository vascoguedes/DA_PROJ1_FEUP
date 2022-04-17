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
     */
    void printShipments();

    void writeShipments();

    void writeExpressShipments();

    void printExpressShipments();

    /**
     * Sorts the Couriers descending, resulting of the following equation:
     * Sqrt(maxVolume^2 + maxWeight^2)
     * @param descending defines sorting order
     */
    void sortCouriers(bool descending);

    /**
     * Sorts the Packages ascending, resulting of the following equation:
     * Sqrt(Volume^2 + Weight^2)
     * @param ascending defines sorting order
     */
    void sortPackages(bool ascending);

    /**
     * TODO
     * @return TODO
     */
    pair<int, int> scenery1();

    /**
     * TODO
     * @return TODO
     */
    vector<Package> backtrackingBestFit(Shipping shipping, vector<Package> packages_all);

    /**
     * TODO
     * @return TODO
     */
    vector<Package> smallerFit(Shipping shipping, vector<Package> packages_all);

    /**
     * Sorts with a Best-Fit algorithm a shipment vector that contains the packages in each courier
     * @return Profit of the shipment
     */
    int scenery2();
    void scenery2_v2();

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
