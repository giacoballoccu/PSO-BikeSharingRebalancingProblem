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
    Station(int demand);
    double getDistanceFrom(const Station& s2);
    int getDemand() const;
    void setDemand(int demand);
    pair<int,int> getCoordinates() const;
private:
    int demand;
    pair<int,int> coordinates;
    int maxX = 100;
    int minX = -100;
    int maxY = 100;
    int minY = - 100;
};
ostream& operator<<(ostream& os, const Station& s);



#endif //BIKEREDISTRIBUTIONHEURISTIC_STATION_H
