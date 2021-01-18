//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_STATION_H
#define BIKEREDISTRIBUTIONHEURISTIC_STATION_H

#include "iostream"
#include "stdio.h"

using namespace std;
class Station {
public:
    Station(){};
    Station(int de) {
        demand = de;
    }
    const int getDemand() const{
        return demand;
    }
private:
    int demand;
};
ostream& operator<<(ostream& os, const Station& s);



#endif //BIKEREDISTRIBUTIONHEURISTIC_STATION_H
