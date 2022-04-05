#include "../include/App.h"
#include "../include/Shipping.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

App::App() = default;

void App::loadData(){
    for(Courier courier : *fileReader.getCourierFromFiles(filepath + "carrinhas.txt")){
        couriers.push_back(courier);
    }
    for(Package package : *fileReader.getPackageFromFiles(filepath + "encomendas.txt")){
        packages.push_back(package);
    }
    sortCouriers();
    sortPackages();
}

/* Auxiliary function for sortCouriers() */
bool comparatorCourier( Courier& i1, Courier& i2) {

    long weight_v1, weight_v2;

    weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
    weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));

    return weight_v1 > weight_v2;
}

void App::sortCouriers() {
    sort(couriers.begin(), couriers.end(), &comparatorCourier);
}

/* Auxiliary function for sortPackages() */
bool comparatorPackage( Package& i1, Package& i2) {

    long weight_v1, weight_v2;

    weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
    weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));

    return weight_v1 < weight_v2;
}

void App::sortPackages() {
    sort(packages.begin(), packages.end(), &comparatorPackage);
}

void App::printCouriers() {
    for(auto line : couriers) {
        cout << line.getMaxWeight() << " " << line.getMaxVolume() << " " << line.getCost() << endl;
    }
}

void App::printPackages() {
    for(auto line : packages) {
        cout << line.getWeight() <<" " <<  line.getVolume() << " " << line.getReward() << " " << line.getDuration() << endl;
    }
}

int App::scenery2() {
    /* NOT YET DONE */
    auto courier = couriers.begin();
    int couriers_size = 0;
    for(const auto& package: packages) {
        int i = 0;
        int min_vol = 1;
        auto shipping = shipments.begin();

        for(;shipping != shipments.end(); shipping++) {
            i++;
            int rem_vol = (int)shipping->getMaxVolume();
            rem_vol -= (int)shipping->getCurrentVolume();
            int package_vol = (int)package.getVolume();
            if(rem_vol >= package_vol) {
                min_vol = 0;
            }
        }
        if(min_vol) {
            if(couriers_size > couriers.size()) continue;
            shipments.emplace_back(Shipping(courier->getMaxVolume(), courier->getMaxWeight(), courier->getCost()));
            courier++;
            couriers_size++;
            shipments.back().pushPackage(package);
            shipments.back().setCurrentVolume(package.getVolume());
            shipments.back().setCurrentWeight(package.getWeight());
            shipments.back().setProfit( (int)package.getReward());
        }
        else {
            shipments.at(i-1).setCurrentVolume(package.getVolume());
            shipments.at(i-1).setCurrentWeight(package.getWeight());
            shipments.at(i-1).setProfit((int)package.getReward());
            shipments.at(i-1).pushPackage(package);
        }
    }
    //printShipments();
    return sortProfits();
}

int App::sortProfits() {
    int i = 0;
    int profits = 0;
    cout << shipments.size() << endl;
    vector<int> positions;
    for(const auto &itr : shipments) {
        if(itr.getProfit() < 0) {
            positions.push_back(i);
        }
        else
            profits+=itr.getProfit();
        i++;
    }
    for(const auto &itr : positions) {
        shipments.erase(shipments.begin() + itr);
    }
    return profits;
}

void App::printShipments() {
    for(const auto& itr : shipments) {
        //if(itr.getShippingSize() == 0) continue;
        cout << itr.getShippingSize()<<endl;
        cout << itr.getCurrentVolume() << "<" << itr.getMaxVolume() << " || ";
        cout << itr.getCurrentWeight() << "<" << itr.getMaxWeight() << " || ";
        cout << itr.getProfit() << endl;
    }
}

int App::scenery3(){
    vector<Package> auxVec;
    vector<Package> expressPackages;
    for(Package package : packages){
        auxVec.push_back(package);
    }
    sort(auxVec.begin(), auxVec.end(), [](const Package &lhs, const Package &rhs) {
        return lhs.getDuration() < rhs.getDuration();
    });

    int timeLeft = 8 * 3600;

    for(Package package : auxVec){
        if(package.getDuration() <= timeLeft) {
            expressPackages.push_back(package);
            timeLeft -= package.getDuration();
        }
        else break;
    }
    return(int)(((8 * 3600) - timeLeft) / expressPackages.size());
}


