#ifndef DA_PROJ1_FEUP_FILEREADER_H
#define DA_PROJ1_FEUP_FILEREADER_H

using namespace std;

#include <iostream>
#include <vector>
#include "Courier.h"
#include "Package.h"

class FileReader {

public:

    /**
     * @brief Class constructor with 3 unsigned objects
     * @param filename Name of the file to be read
     */
    vector<string> fileReader(string filename);

    /**
     * @brief Reads couriers from file to vector couriers
     * @param filename Name of the file to be read
     */
    vector<Courier> *getCourierFromFiles(string f1);

    /**
     * @brief Reads packages from file to vector packages
     * @param filename Name of the file to be read
     */
    vector<Package> *getPackageFromFiles(string f1);

};

#endif //DA_PROJ1_FEUP_FILEREADER_H
