//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_OPTIMIZER_H
#define BIKEREDISTRIBUTIONHEURISTIC_OPTIMIZER_H

#include <vector>
#include "stdio.h"
#include "iostream"
using namespace std;

class Optimizer {
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    void KnuthShuffle(vector<int>& arr);
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_OPTIMIZER_H
