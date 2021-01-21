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
    void readFromDataset(string path);
    int noOfStations = 4;
    int noOfVehicles = 1;
    int MAXIMUM_STATION_DEMAND = 7;
    int N_PARTICLES = 7;
    int N_ITERATIONS = 12;
    int DEPOT_DEMAND = 5;
    vector<int> vehicleCapacity = {10};
};

#endif // SIMULATOR_H



