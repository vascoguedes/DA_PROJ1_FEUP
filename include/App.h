#ifndef DA_PROJ1_FEUP_APP_H
#define DA_PROJ1_FEUP_APP_H

#include "FileReader.h"
#include "Shipping.h"

class App{
private:
    FileReader fileReader;
    string filepath = "../dataFiles/";
    vector<Courier> couriers;
    vector<Package> packages;
    vector<Shipping> shipments;
public:
    App();
    void loadData();
    void printCouriers();
    void printPackages();
    void printShipments();
    /**
     * Sorts the Couriers ascending, resulting of the following equation:
     * Sqrt(maxVolume^2 + maxWeight^2)
     */
    void sortCouriers();
    /**
     * Sorts the Packages descending, resulting of the following equation:
     * Sqrt(Volume^2 + Weight^2)
     */
    void sortPackages();
    int scenery2();
    int sortProfits();
    int scenery3();
};

#endif //DA_PROJ1_FEUP_APP_H
