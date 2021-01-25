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
    int start(string path="", string log="");
    void readFromDataset(string path);
    int noOfStations = 8;
    int noOfVehicles = 1;
    int MAXIMUM_STATION_DEMAND = 10;
    int N_PARTICLES = 100000;
    int N_ITERATIONS = 1000;
    vector<int> vehicleCapacity = {15};
};

#endif // SIMULATOR_H



