#ifndef DA_PROJ1_FEUP_FILEREADER_H
#define DA_PROJ1_FEUP_FILEREADER_H

using namespace std;

#include <iostream>
#include <vector>
#include "Courier.h"

vector<string> fileReader(string filename);

vector<Courier> *getCourierFromFiles(string f1);



#endif //DA_PROJ1_FEUP_FILEREADER_H
