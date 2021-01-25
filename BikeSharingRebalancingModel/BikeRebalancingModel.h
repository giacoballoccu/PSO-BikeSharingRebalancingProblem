//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H
#define BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H

#include <vector>
#include <unordered_map>
#include <map>
#include "Vehicle.h"
#include "Station.h"
#include "stdio.h"
#include "iostream"

using namespace std;

class BikeRebalancingModel {
public:
    BikeRebalancingModel(string filename);
    BikeRebalancingModel(int nStations, vector<int> vehicleCapacity, int nVehicles, int msd);
    map<int,Station> dropoffStations;
    map<int,Station> pickupStations;
    void printModelDetails();
    unordered_map<string, vector<int>> analyzeOptimalRoute(vector<int> optimalRoute);
    unordered_map<string, vector<int>> analyzeOptimalRouteSimultaneous(vector<int> optimalRoute);
    int getRandomDemand(const int max) const;
    int getNOfStations() const;

    int getNOfVehicles() const;

    const vector<vector<double>> &getDistanceMatrix() const;

    const vector<Station> &getStations() const;

    const vector<Vehicle> &getVehicles() const;

private:
    vector<Station> stations;

    vector<Vehicle> vehicles;
    int nOfStations;
    int nOfVehicles;
    vector<vector<double>> distanceMatrix;
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H
