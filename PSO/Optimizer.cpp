//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "Optimizer.h"

void Optimizer::KnuthShuffle(vector<int>& arr){
    for (int i = arr.size() - 1; i > 0; i--)
    {
        int index = rand() % i+1;
        swap(arr[index], i);
    }
}