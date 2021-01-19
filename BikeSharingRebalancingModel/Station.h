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
        int x = rand() % maxX + minX;
        int y = rand() % maxY + minY;
        Station::coordinates = make_pair(x,y);
    }
    double getDistanceFrom(Station s2);
    int getDemand() const{
        return demand;
    }
    int getOffer() const{
        return offer;
    }
    pair<int,int> getCoordinates() const{
        return coordinates;
    }
private:
    int demand;
    int offer;
    pair<int,int> coordinates;
    int maxX = 100;
    int minX = -100;
    int maxY = 100;
    int minY = - 100;
};
ostream& operator<<(ostream& os, const Station& s);



#endif //BIKEREDISTRIBUTIONHEURISTIC_STATION_H
