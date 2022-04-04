#include "../include/App.h"

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

