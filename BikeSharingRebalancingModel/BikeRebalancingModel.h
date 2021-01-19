//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H
#define BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H

#include <vector>
#include <unordered_map>
#include "Vehicle.h"
#include "Station.h"
#include "stdio.h"
#include "iostream"
using namespace std;
class BikeRebalancingModel {
public:
    BikeRebalancingModel(int nStations, vector<int> vehicleCapacity, int nVehicles , int msd, int msr){
        nOfStations = nStations;
        nOfVehicles = nVehicles;
        distanceMatrix = vector<vector<double>>(nStations+1, vector<double>(nStations+1, 0));
        stations = vector<Station>(nStations+1, Station());
        vehicles = vector<Vehicle>(nVehicles, Vehicle());



        for(int i=0; i<nOfStations+1; i++){
            int demand = getRandomDemand(msd);
            int rec = getRandomDemand(msr);
            if( rec > demand){
                int temp = demand;
                demand = rec;
                rec = temp;
            }
            else if(rec == demand)
                rec--;
            stations[i] = Station(demand, rec);
        }

        //initialize the distance between stores and store demands
        for(int i=0; i<stations.size(); i++){
            for(int j=i; j<stations.size(); j++){
                if(i==j)
                    distanceMatrix[i][j] = 0;
                else
                    distanceMatrix[i][j] = distanceMatrix[j][i] = stations[i].getDistanceFrom(stations[j]);
            }
        }
        //initialize capacity of each Vehicle
        for(int i=0; i<nOfVehicles; i++){
            vehicles[i] = Vehicle(vehicleCapacity[i]);
        }
    }
    void printModelDetails();
    unordered_map<string, vector<int>> analyzeOptimalRoute(vector<int> optimalRoute);
    unordered_map<string, vector<int>> analyzeOptimalRouteSimultaneous(vector<int> optimalRoute);
    int getRandomDistance(int max){
        return rand() % max + 1;
    }
    int getRandomDemand(int max){
        return rand() % max + 1;
    }
private:
    int nOfStations;
    int nOfVehicles;

    vector<vector<double>> distanceMatrix;
public:
    int getNOfStations() const;

    int getNOfVehicles() const;

    const vector<vector<double>> &getDistanceMatrix() const;

    const vector<Station> &getStations() const;

    const vector<Vehicle> &getVehicles() const;

private:
    vector<Station> stations;
    vector<Vehicle> vehicles;
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_BIKEREBALANCINGMODEL_H
