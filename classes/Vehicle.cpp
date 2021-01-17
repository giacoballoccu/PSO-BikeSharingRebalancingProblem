//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "Vehicle.h"
#include "iostream"
const string Vehicle::to_string() const{
    cout << "Vehicle [capacity=" << getCapacity() << "]";
};
ostream& operator<<(ostream& os, const Vehicle& v)
{
    os << "Vehicle [capacity=" << v.getCapacity() << "]";
    return os;
}