//
// Created by Giacomo Balloccu on 18/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_PSOUTILS_H
#define BIKEREDISTRIBUTIONHEURISTIC_PSOUTILS_H

#include "stdio.h"
#include "vector"
using namespace std;

namespace PSOutils {
    string doubleVectorToString(vector<double> v);
    string intVectorToString(vector<int> v);
    void KnuthShuffle(vector<int>& arr);
    vector<double> copyVecIntToVecDouble(const vector<int> vec);
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_PSOUTILS_H
