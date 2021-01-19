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
    Station(int demand, int offer) {
        Station::demand = demand;
        Station::offer = offer;
    }
    int getDemand() const{
        return demand;
    }
    int getOffer() const{
        return offer;
    }
private:
    int demand;
    int offer;
};
ostream& operator<<(ostream& os, const Station& s);



#endif //BIKEREDISTRIBUTIONHEURISTIC_STATION_H
