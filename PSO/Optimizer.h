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
    void KnuthShuffle(vector<int> arr){
        for (int i = arr.size() - 1; i > 0; i--)
        {
            int index = rand() % i+1;
            swap(arr[index], i);
        }
    }
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_OPTIMIZER_H
