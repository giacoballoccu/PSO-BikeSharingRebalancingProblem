//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include <cmath>
#include "Station.h"
#include "iostream"
using namespace std;

Station::Station(int demand) {
    Station::demand = demand;
    int x = rand() % maxX + minX;
    int y = rand() % maxY + minY;
    Station::coordinates = make_pair(x,y);
}
int Station::getDemand() const{
    return demand;
}
void Station::setDemand(int demand){
    Station::demand = demand;
}
pair<int,int> Station::getCoordinates() const{
    return coordinates;
}

double Station::getDistanceFrom(const Station& s2){
    double x = coordinates.first - s2.getCoordinates().first; //calculating number to square in next step
    double y = coordinates.second - s2.getCoordinates().second;
    double dist;

    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

ostream& operator<<(ostream& os, const Station& s)
{
    string node_label;
    if(s.getDemand() == 0) {
        os << "Depot [demand=" << s.getDemand() << "]";
        return os;
    }else{
        node_label = s.getDemand() > 0 ? "Dropoff " : "Pickup  ";
    }
    os << node_label << " Station [demand=" << s.getDemand() << "]";
    return os;
}
