//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_VEHICLE_H
#define BIKEREDISTRIBUTIONHEURISTIC_VEHICLE_H
#include "ostream"
#include "stdio.h"
using namespace std;

class Vehicle {
public:
    Vehicle(){};
    Vehicle(int cap){
        capacity = cap;
    }
    const int getCapacity() const {
        return capacity;
    }
    const string to_string() const;
private:
    int capacity;

};
ostream& operator<<(ostream& os, const Vehicle& v);


#endif //BIKEREDISTRIBUTIONHEURISTIC_VEHICLE_H
