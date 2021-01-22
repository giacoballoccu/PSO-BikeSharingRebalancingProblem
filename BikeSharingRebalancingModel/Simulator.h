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
    int start(string filename="");
    void readFromDataset(string path);
    int noOfStations = 15;
    int noOfVehicles = 2;
    int MAXIMUM_STATION_DEMAND = 10;
    int N_PARTICLES = 30;
    int N_ITERATIONS = 12;
    vector<int> vehicleCapacity = {15, 15};
};

#endif // SIMULATOR_H



