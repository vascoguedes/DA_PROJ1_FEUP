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
            sort(couriers.begin(), couriers.end(), []( Courier& i1, Courier& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
                weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
                return weight_v1 > weight_v2;
            });
            break;
        case 2:
            sort(couriers.begin(), couriers.end(), []( Courier& i1, Courier& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
                weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
                return weight_v1 < weight_v2;
            });
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
            sort(couriers.begin(), couriers.end(), []( Courier& i1, Courier& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
                weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
                return weight_v1 > weight_v2;
            });
    }
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
            sort(packages.begin(), packages.end(), []( Package& i1, Package& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
                weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
                return weight_v1 < weight_v2;
            });
            break;
        case 2:
            sort(packages.begin(), packages.end(), []( Package& i1, Package& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
                weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
                return weight_v1 > weight_v2;
            });
            break;
        case 3:
            sort(packages.begin(), packages.end(), [&packages_max_reward, &packages_max_volume, &packages_max_weight]( Package& i1, Package& i2){
                double weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getVolume()*100 / packages_max_volume, 2) + pow(i1.getWeight()*100 /packages_max_weight, 2));
                weight_v1 -= (double)(100*i1.getReward())/packages_max_reward;

                weight_v2 = sqrt(pow(i2.getVolume()*100 / packages_max_volume, 2) + pow(i2.getWeight()*100 /packages_max_weight, 2));
                weight_v2 -= (double)(100*i2.getReward())/packages_max_reward;
                return weight_v1 < weight_v2;
            });
            break;
        default:
            sort(packages.begin(), packages.end(), []( Package& i1, Package& i2) {
                long weight_v1, weight_v2;
                weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
                weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
                return weight_v1 < weight_v2;
            });
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
    file.open(filepath + "shipments.txt", ofstream::out | ofstream::trunc);
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

void App::unloadShipments() {
    for(auto courier : couriers) {
        courier.getShipping().clearPackages();
    }
    shipments.clear();
}

void App::printShipments(int scenery) {
    int package_size = 0;
    for(const auto& itr : shipments) {
        package_size += itr.getShippingSize();
        cout << "Courier ID: " << itr.getID() << endl;
        cout << "Shipped packages: " << itr.getShippingSize() << endl;
        cout << itr.getCurrentVolume() << " / " << itr.getMaxVolume() << " || ";
        cout << itr.getCurrentWeight() << " / " << itr.getMaxWeight();
        if(scenery == 2) cout << " || "<< itr.getProfit();
        cout << endl;
    }
    cout << endl << "Amount of shipped packages:" << package_size << endl;
    cout << "Amount of couriers used:" << shipments.size() << endl;
}

/******* SCENERY 1 FUNCTIONS *******/

vector<int> knapSackScenery1( Courier& courier, vector<Package> packages) {
    int max_wei = (int)courier.getMaxWeight();
    int max_vol = (int)courier.getMaxVolume();

    vector<vector<vector<int> > > dp = vector<vector<vector <int>>>(packages.size()+1, vector<vector<int>>(courier.getMaxWeight()+1, vector<int>(courier.getMaxVolume()+1, 0)));

    for(int i = 1; i < packages.size(); i++) {
        int wei = (int)(packages.begin() + i-1)->getWeight(), rew = 1, vol =(int)(packages.begin() + i-1)->getVolume();
        for(int j = 0; j <= max_wei; j++) {
            for(int k = 0; k <=max_vol; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j >= wei && k >= vol && dp[i][j][k] < (dp[i - 1][j - wei][k - vol] + rew)) {
                    dp[i][j][k] = dp[i - 1][j - wei][k - vol] + rew;
                }
            }
        }
    }
    int sum_wei = 0, sum_vol = 0;
    int n = (int)packages.size();
    vector<int> ret;
    while(n>0) {
        if(dp[n][max_wei][max_vol] != dp[n-1][max_wei][max_vol]) {
            max_wei -= (int)(packages.begin() + (n-1))->getWeight();
            max_vol -= (int)(packages.begin() + (n-1))->getVolume();
            sum_wei += (int)(packages.begin() + (n-1))->getWeight();
            sum_vol += (int)(packages.begin() + (n-1))->getVolume();
            ret.push_back(n-1);
        }
        n--;
    }
    return ret;
}

int App::scenery1() {
    for (Package &aPackage: packages) {
        aPackage.setAssignedValue(false);
    }
    unloadShipments();
    sortCouriers(1);
    sortPackages(2);

    vector<Package> aux_packages = packages;

    for(auto courier: couriers) {
        auto sort = knapSackScenery1(courier, aux_packages);

        if(sort.empty()) continue;
        shipments.emplace_back(Shipping(courier.getID(), courier.getMaxVolume(), courier.getMaxWeight(), 0));

        for(auto each: sort)
            shipments.back().pushPackage(aux_packages.at(each));

        for(auto each: sort)
            aux_packages.erase(aux_packages.begin() + each);

    }

    return shipments.size();
}

/***********************************/

/******* SCENERY 2 FUNCTIONS *******/

void App::bestFitAlgorithm() {
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
            shipments.emplace_back(Shipping(courier->getID(), courier->getMaxVolume(), courier->getMaxWeight(), courier->getCost()));
            courier++;
            couriers_size++;
            shipments.back().pushPackage(package);
        }
        else {
            shipments.at(i-1).pushPackage(package);
        }
        package.setAssignedValue(true);
    }
}

vector<int> knapSack( Courier& courier, vector<Package> packages) {
    int max_wei = (int)courier.getMaxWeight();
    int max_vol = (int)courier.getMaxVolume();

    vector<vector<vector<int> > > dp = vector<vector<vector <int>>>(packages.size()+1, vector<vector<int>>(courier.getMaxWeight()+1, vector<int>(courier.getMaxVolume()+1, 0)));

    for(int i = 1; i < packages.size(); i++) {
        int wei = (int)(packages.begin() + i-1)->getWeight(), rew = (int)(packages.begin() + i-1)->getReward(), vol =(int)(packages.begin() + i-1)->getVolume();
        for(int j = 0; j <= max_wei; j++) {
            for(int k = 0; k <=max_vol; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j >= wei && k >= vol && dp[i][j][k] < (dp[i - 1][j - wei][k - vol] + rew)) {
                    dp[i][j][k] = dp[i - 1][j - wei][k - vol] + rew;
                }
            }
        }
    }

    int sum_wei = 0, sum_vol = 0;
    int n = (int)packages.size();

    vector<int> ret;
    while(n>0) {
        if(dp[n][max_wei][max_vol] != dp[n-1][max_wei][max_vol]) {
            max_wei -= (int)(packages.begin() + (n-1))->getWeight();
            max_vol -= (int)(packages.begin() + (n-1))->getVolume();
            sum_wei += (int)(packages.begin() + (n-1))->getWeight();
            sum_vol += (int)(packages.begin() + (n-1))->getVolume();
            ret.push_back(n-1);
        }
        n--;
    }
    return ret;
}

void App::knapSackAlgorithm() {
    vector<Package> aux_packages = packages;
    for(auto& courier: couriers) {
        if(aux_packages.empty()) break;
        auto sort = knapSack(courier, aux_packages);
        shipments.emplace_back(Shipping(courier.getID(), courier.getMaxVolume(), courier.getMaxWeight(), courier.getCost()));
        for(auto each: sort)
            shipments.back().pushPackage(aux_packages.at(each));

        if(shipments.back().getProfit() > 0)
            for(auto each: sort)
                aux_packages.erase(aux_packages.begin() + each);
        else
            shipments.erase(shipments.end());
    }
}

int App::scenery2(bool knapsack_algorithm) {
    for (Package &aPackage: packages) {
        aPackage.setAssignedValue(false);
    }
    // Best fit Algorithm
    unloadShipments();
    sortPackages(3);
    sortCouriers(3);

    if(knapsack_algorithm)
        knapSackAlgorithm();
    else
        bestFitAlgorithm();


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
    for(auto itr = positions.rbegin(); itr != positions.rend(); itr++) {
        auto ids = (shipments.begin() + *itr)->getPackages();
        for(auto id : ids) {
            for(auto package : packages) {
                if(package.getID() == id.getID())
                    package.setAssignedValue(false);
            }
        }
        shipments.erase(shipments.begin() + *itr);
    }

    return profits;
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



