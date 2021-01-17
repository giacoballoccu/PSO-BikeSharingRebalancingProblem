//
// Created by Giacomo Balloccu on 17/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_HEURISTICMODEL_H
#define BIKEREDISTRIBUTIONHEURISTIC_HEURISTICMODEL_H

#include <vector>
#include "Vehicle.h"
#include "Station.h"
#include "stdio.h"
#include "iostream"
using namespace std;
class HeuristicModel {
public:
    HeuristicModel(int nStations, vector<int> vehicleCapacity, int nVehicles ,int msd, int msr){
        noOfStations = nStations;
        noOfVehicles = nVehicles;
        distanceMatrix = vector<vector<double>>(nStations+1, vector<double>(nStations+1, 0));
        stations = vector<Station>(nStations, Station(0));
        vehicles = vector<Vehicle>(nVehicles, Vehicle(0));

        //initialize the distance between stores and store demands
        for(int i=1; i<noOfStations+1; i++){
            for(int j=i; j<noOfStations+1; j++){
                if(i==j)
                    distanceMatrix[i][j] = 0;
                else
                    distanceMatrix[i][j] = distanceMatrix[j][i] = getRandomDistance(50);
            }
        }

        for(int i=0; i<noOfStations; i++){
            int demand = getRandomDemand(msd);
            int rec = getRandomDemand(msr);
            if( rec > demand){
                int temp = demand;
                demand = rec;
                rec = temp;
            }
            else if(rec == demand)
                rec--;
            stations[i] = Station(demand);
        }

        //initialize capacity of each Vehicle
        for(int i=0; i<noOfVehicles; i++){
            vehicles[i] = Vehicle(vehicleCapacity[i]);
        }
    }
    void printModelDetails();
    int getRandomDistance(int max){
        return rand() % max + 1;
    }
    int getRandomDemand(int max){
        return rand() % max + 1;
    }
private:
    int noOfStations;
    int noOfVehicles;

    vector<vector<double>> distanceMatrix;
    vector<Station> stations;
    vector<Vehicle> vehicles;
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_HEURISTICMODEL_H
