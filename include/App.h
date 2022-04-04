#ifndef DA_PROJ1_FEUP_APP_H
#define DA_PROJ1_FEUP_APP_H

#include "FileReader.h"

class App{
private:
    FileReader fileReader;
    string filepath = "../dataset/";
    vector<Courier> couriers;
    vector<Package> packages;
public:
    App();
    void loadData();
    int scenery3();
};

#endif //DA_PROJ1_FEUP_APP_H
