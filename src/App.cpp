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

void App::sortCouriers(int sort_algorithm) {

    int courier_max_volume = 0, courier_max_weight = 0, courier_max_cost = 0; // Auxiliar parameters

    for(auto& courier : couriers) {
        if(courier.getCost() > courier_max_cost)
            courier_max_cost = courier.getCost();
        if(courier.getMaxWeight() > courier_max_weight)
            courier_max_weight = courier.getMaxWeight();
        if(courier.getMaxVolume() > courier_max_volume)
            courier_max_volume = courier.getMaxVolume();
    }

    switch (sort_algorithm) {
        case 1:
            sort(couriers.begin(), couriers.end(), &comparatorCourier);
            break;
        case 2:
            sort(couriers.begin(), couriers.end(), &reverseComparatorCourier);
            break;
        case 3:
            sort(couriers.begin(), couriers.end(), [&courier_max_cost, &courier_max_volume, &courier_max_weight](Courier& i1, Courier& i2) {
                double weight_v1, weight_v2;
                weight_v1 = sqrt(pow(100*i1.getMaxVolume(), 2) + pow(100*i1.getMaxWeight(), 2));
                weight_v1 /= sqrt(pow(courier_max_volume, 2) + pow(courier_max_weight, 2));
                weight_v1 -= (double)(100*i1.getCost())/courier_max_cost;

                weight_v2 = sqrt(pow(100*i2.getMaxVolume(), 2) + pow(100*i2.getMaxWeight(), 2));
                weight_v2 /= sqrt(pow(courier_max_volume, 2) + pow(courier_max_weight, 2));
                weight_v2 -= (double)(100*i2.getCost())/courier_max_cost;

                return weight_v1 > weight_v2;
            });
            break;
        default:
            sort(couriers.begin(), couriers.end(), &comparatorCourier);
    }
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

void App::sortPackages(int sort_algorithm) {
    int packages_max_reward = 0, packages_max_weight = 0, packages_max_volume = 0;
    for(const auto& package : packages) {
        if(package.getReward() > packages_max_reward)
            packages_max_reward = package.getReward();
        if(package.getWeight() > packages_max_weight)
            packages_max_weight = package.getWeight();
        if(package.getVolume() > packages_max_volume)
            packages_max_volume = package.getVolume();
    }
    switch (sort_algorithm) {
        case 1:
            sort(packages.begin(), packages.end(), &comparatorPackage);
            break;
        case 2:
            sort(packages.begin(), packages.end(), &reverseComparatorPackage);
            break;
        case 3:
            sort(packages.begin(), packages.end(), [this, &packages_max_reward, &packages_max_volume, &packages_max_weight]( Package& i1, Package& i2){
                double weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getVolume()*100 / packages_max_volume, 2) + pow(i1.getWeight()*100 /packages_max_weight, 2));
                weight_v1 -= (double)(100*i1.getReward())/packages_max_reward;

                weight_v2 = sqrt(pow(i2.getVolume()*100 / packages_max_volume, 2) + pow(i2.getWeight()*100 /packages_max_weight, 2));
                weight_v2 -= (double)(100*i2.getReward())/packages_max_reward;
                return weight_v1 < weight_v2;
            });
            break;
        default:
            sort(packages.begin(), packages.end(), &comparatorPackage);
    }
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

/******* SCENERY 1 FUNCTIONS *******/

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

/***********************************/

/******* SCENERY 2 FUNCTIONS *******/

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

/******* SCENERY 3 FUNCTIONS *******/

int App::scenery3(){
    sort(packages.begin(), packages.end(), [](const Package &lhs, const Package &rhs) {
        if(lhs.getDaysPast() == rhs.getDaysPast())
            return lhs.getDuration() < rhs.getDuration();
        return lhs.getDaysPast() < rhs.getDaysPast();
    });

    int timeLeft = 8 * 3600;
    int sum = 0;
    int total_sum=0;

    unsigned int count = 0;
    for(vector<Package>::iterator it = packages.begin(); it < packages.end(); it++){
        if((*it).getDuration() <= timeLeft) {
            expressPackages.push_back((*it));
            timeLeft -= (*it).getDuration();
            sum += (*it).getDuration();
            total_sum +=sum;
            packages.erase(it);
            count++;
            it--;
        }
        else {
            (*it).increaseDaysPast();
        }
    }

    return(int)((total_sum) / count);
}

/***********************************/



