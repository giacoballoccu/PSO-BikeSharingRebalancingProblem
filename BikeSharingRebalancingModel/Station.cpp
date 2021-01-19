//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include <cmath>
#include "Station.h"
#include "iostream"
using namespace std;
double Station::getDistanceFrom(Station s2){
    double x = coordinates.first - s2.getCoordinates().first; //calculating number to square in next step
    double y = coordinates.second - s2.getCoordinates().second;
    double dist;

    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

ostream& operator<<(ostream& os, const Station& s)
{
    os << "Store [demand=" << s.getDemand() << "]" << " [offer=" << s.getOffer() << "]";
    return os;
}
