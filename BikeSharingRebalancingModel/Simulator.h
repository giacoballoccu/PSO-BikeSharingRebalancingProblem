#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "BikeSharingRebalancingModel/BikeRebalancingModel.h"
#include "PSOImplementation/Swarm.h"
#include "PSOImplementation/PSOUtils.h"
using namespace std;

class Simulator
{
public:
    Simulator();
    int start();
    int noOfStations = 12;
    int noOfVehicles = 1;
    int MAXIMUM_STATION_DEMAND = 6;
    int MAXIMUM_STATION_OFFERT = 6;
    int N_PARTICLES = 3;
    int N_ITERATIONS = 100;
};

#endif // SIMULATOR_H



