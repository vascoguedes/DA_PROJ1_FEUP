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
     * Sorts the Couriers descending, resulting of the following equation:
     * Sqrt(maxVolume^2 + maxWeight^2)
     */
    void sortCouriers(bool descending);
    /**
     * Sorts the Packages ascending, resulting of the following equation:
     * Sqrt(Volume^2 + Weight^2)
     */
    void sortPackages(bool ascending);
    int scenery2();
    void unloadShipments();
    int sortProfits();
    int scenery3();
};

#endif //DA_PROJ1_FEUP_APP_H
