#include "../include/FileReader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

vector<string> FileReader::fileReader(string filename){
    ifstream my_file;
    string line;

    vector<string> ret;

    my_file.open(filename, ios::out);
    if (my_file.is_open()) {
        getline(my_file, line); //to not read the first line
        while(getline(my_file, line)) {
            ret.push_back(line);
        }
        my_file.close();
    }
    return ret;
}

bool fileExists(string f_name) {
    ifstream f;
    f.open(f_name);
    if(f.is_open()) {
        f.close();
        return true;
    }
    else {
        cout << "File does not exists" << endl;
        return false;
    }
}



vector<Courier> *FileReader::getCourierFromFiles(string f1) {
    vector<Courier> * couriers = new vector<Courier>;
    vector<string> ret;
    if(!fileExists(f1)) return nullptr;
    ret = fileReader(f1);
    for(auto line : ret) {
        stringstream ss(line);
        unsigned maxVolume, maxWeight, cost;
        ss >> maxVolume;
        ss >> maxWeight;
        ss >> cost;
        couriers->push_back(Courier(maxVolume, maxWeight, cost));
    }
    return couriers;
}

vector<Package> *FileReader::getPackageFromFiles(string f1) {
    vector<Package> * package = new vector<Package>;
    vector<string> ret;
    if(!fileExists(f1)) return nullptr;
    ret = fileReader(f1);
    for(auto line : ret) {
        stringstream ss(line);
        unsigned volume, weight, reward, duration;
        ss >> volume;
        ss >> weight;
        ss >> reward;
        ss >> duration;
        package->push_back(Package(volume, weight, reward, duration));
    }
    return package;
}





