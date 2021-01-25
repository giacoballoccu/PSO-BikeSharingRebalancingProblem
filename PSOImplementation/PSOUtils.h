#ifndef PSOUTILS_H
#define PSOUTILS_H

#include "stdio.h"
#include "vector"
using namespace std;

namespace PSOutils {
    string doubleVectorToString(vector<double> v);
    string intVectorToString(vector<int> v);
    void KnuthShuffle(vector<int>& arr);
    double normalizeValue(int min, int max);
    vector<double> copyVecIntToVecDouble(const vector<int> vec);
    vector<int> copyVecDoubleToVecInt(const vector<double> vec);
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_PSOUTILS_H
