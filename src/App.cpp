#include "../include/App.h"
#include "../include/Shipping.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>

App::App() = default;

void App::loadData(){
    for(Courier courier : *fileReader.getCourierFromFiles(filepath + "carrinhas.txt")){
        couriers.push_back(courier);
    }
    for(Package package : *fileReader.getPackageFromFiles(filepath + "encomendas.txt")){
        packages.push_back(package);
    }
    sortCouriers(true);
    sortPackages(true);
}

/* Auxiliary function for sortCouriers() */
bool comparatorCourier( Courier& i1, Courier& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
    weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
    return weight_v1 > weight_v2;
}
bool reverseComparatorCourier( Courier& i1, Courier& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
    weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
    return weight_v1 < weight_v2;
}

void App::sortCouriers(bool descending) {
    if(descending)
        sort(couriers.begin(), couriers.end(), &comparatorCourier);
    else
        sort(couriers.begin(), couriers.end(), &reverseComparatorCourier);
}

/* Auxiliary function for sortPackages() */
bool comparatorPackage( Package& i1, Package& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
    weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
    return weight_v1 < weight_v2;
}
bool reverseComparatorPackage( Package& i1, Package& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
    weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
    return weight_v1 > weight_v2;
}

void App::sortPackages(bool ascending) {
    if(ascending)
        sort(packages.begin(), packages.end(), &comparatorPackage);
    else
        sort(packages.begin(), packages.end(), &reverseComparatorPackage);
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

void App::writeShipments() {
    fstream file;
    file.open(filepath + "shippments.txt", ofstream::out | ofstream::trunc);
    if (!file.is_open()) {
        cerr << "Unable to open file";
        exit(1);
    }
    for(const Courier &courier : couriers){
        file << "Courier:" << courier;
        file << "Package:\n";
        for(const Package &package : courier.getShipping().getPackages()){
            file<< "->" << package;
        }
    }
    file.close();
}

void App::writeExpressShipments() {
    fstream file;
    file.open(filepath + "expressShippments.txt", ofstream::out | ofstream::trunc);
    if (!file.is_open()) {
        cerr << "Unable to open file";
        exit(1);
    }
    int count = 0;
    int daysPast = 0;
    file << "Express Packages:\n";
    file << "Day " << daysPast + 1 << ":\n";
    for(const Package &package : expressPackages){
        if(daysPast != package.getDaysPast()) {
            daysPast++;
            file << "Day " << daysPast + 1 << ":\n";
        }
        count++;
        file << count << "º: " << package << "\n";
    }
    file.close();
}

void App::printExpressShipments() {
    cout << "Express Packages:\n";
    int count = 0;
    int daysPast = 0;
    cout << "Day " << daysPast + 1 << ":" << endl;
    for(const Package &package : expressPackages){
        if(daysPast != package.getDaysPast()) {
            daysPast++;
            cout << "Day " << daysPast + 1 << ":" << endl;
        }
        count++;
        cout << count << "\370: " << package << endl;
    }
}

/******* SCENERY 1 FUNCTIONS ******/

pair<int, int> App::scenery1() {

    for (Package &aPackage: packages) {
        aPackage.setAssignedValue(false);
    }

    int count = 1, numCouriers = 0, numPackages = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (Courier &courier: couriers) {
        cout << "NOVO HOME " << count << endl;
        courier.getShipping().cleanPackage();
        vector<Package> aux = smallerFit(courier.getShipping(), packages);//backtrackingBestFit(courier.getShipping(), packages);
        cout << "acabou, size: " << aux.size()  << endl;

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
        if (!aux.empty()){
            numCouriers++;
            numPackages += aux.size();
        }
        for (const Package & aPackage: aux) {
            for (Package & aPackage1: packages) {
                if (!aPackage1.getAssignedValue() && aPackage.getWeight() == aPackage1.getWeight() && aPackage.getVolume() == aPackage1.getVolume()) {
                    aPackage1.setAssignedValue(true);
                    break;
                }
            }
        }
        count++;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
    return make_pair(numCouriers, numPackages);
}

vector<Package> App::backtrackingBestFit(Shipping shipping, vector<Package> package_all) {
    if (shipping.isFull()) return shipping.getPackages();
    vector<Package> result = shipping.getPackages();

    for (Package &package: package_all) {
        if (shipping.canFit(package) && !package.getAssignedValue()) {
            shipping.pushPackage(package);

            vector<Package> aux = backtrackingBestFit(shipping, package_all);

            if (aux.size() > result.size()) { result = aux;
                if (result.size() == package_all.size()) return result;}

            shipping.removePackage(package);
        }
    }

    return result;
}

vector<Package> App::smallerFit(Shipping shipping, vector<Package> packages_all) {

    for (Package &package: packages_all) {
        if (shipping.canFit(package) && !package.getAssignedValue() && shipping.aTenthFree()) {
            shipping.pushPackage(package);
        }
    }

    vector<Package> aux = backtrackingBestFit(shipping, packages_all);

    cout << "PESO FINAL: " << shipping.getCurrentWeight() << " / " << shipping.getMaxWeight() << endl;
    cout << "VOLUME FINAL: " << shipping.getCurrentVolume() << " / " << shipping.getMaxVolume() << endl;

    return aux;
}

/******* SCENERY 2 FUNCTIONS ******/

int App::scenery2() {
    /* NOT YET DONE */
    unloadShipments();

    auto courier = couriers.begin();
    int couriers_size = 0;
    for(auto& package: packages) {
        int i = 0;
        int verifier = 1;
        auto shipping = shipments.begin();

        for(;shipping != shipments.end(); shipping++) {
            i++;
            int rem_vol = (int)shipping->getMaxVolume();
            rem_vol -= (int)shipping->getCurrentVolume();
            rem_vol -= (int)package.getVolume();

            int rem_wei = (int)shipping->getMaxWeight();
            rem_wei -= (int)shipping->getCurrentWeight();
            rem_wei -= (int)package.getWeight();

            if(rem_vol >= 0 && rem_wei >= 0) {
                verifier = 0;
                break;
            }
        }
        if(verifier) {
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
    vector<int> positions;
    for(const auto &itr : shipments) {
        if(itr.getProfit() < 0)
            positions.push_back(i);
        else
            profits+=itr.getProfit();
        i++;
    }
    for(auto itr = positions.rbegin(); itr != positions.rend(); itr++)
        shipments.erase(shipments.begin() + *itr);

    return profits;
}

void App::unloadShipments() {
    shipments.clear();
}

void App::printShipments() {
    int package_size = 0;
    for(const auto& itr : shipments) {
        package_size += itr.getShippingSize();
        cout << itr.getShippingSize()<<endl;
        cout << itr.getCurrentVolume() << "<" << itr.getMaxVolume() << " || ";
        cout << itr.getCurrentWeight() << "<" << itr.getMaxWeight() << " || ";
        cout << itr.getProfit() << endl;
    }
    cout << endl << package_size << endl;
}

/***********************************/

int App::scenery3(){
    sort(packages.begin(), packages.end(), [](const Package &lhs, const Package &rhs) {
        if(lhs.getDaysPast() == rhs.getDaysPast())
            return lhs.getDuration() < rhs.getDuration();
        return lhs.getDaysPast() < rhs.getDaysPast();
    });

    int timeLeft = 8 * 3600;

    unsigned int count = 0;
    for(vector<Package>::iterator it = packages.begin(); it < packages.end(); it++){
        if((*it).getDuration() <= timeLeft) {
            expressPackages.push_back((*it));
            timeLeft -= (*it).getDuration();
            packages.erase(it);
            count++;
            it--;
        }
        else {
            (*it).increaseDaysPast();
        }
    }

    return(int)(((8 * 3600) - timeLeft) / count);
}




void App::scenery2_v2() {
    

}


