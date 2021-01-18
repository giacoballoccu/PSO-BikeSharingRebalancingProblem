//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "BikeRebalancingModel.h"
#include "stdio.h"
#include "iostream"
void BikeRebalancingModel::printModelDetails(){

    cout << "No Of Stores : " << nOfStations << endl;
    cout << "Store Details : ";
    for(Station s: stations)
        cout << s << " ";
    cout << "\n";
    cout << "No Of Vehicles : "  << nOfVehicles << endl;
    for(Vehicle v: vehicles)
        cout << v << " ";
    cout << "\n";
    cout << "Distance Matrix : ";
    cout << "\tDepot\t";
    for(int k=0; k<stations.size();k++)
        cout << "Station" << (k+1) << "\t";
    cout << endl;

    for(int i=0; i<distanceMatrix.size(); i++){
        string name;
        if(i == 0 or i == nOfStations){
            name = "Depot\t";
        }else{
            name = "Station";
            name.push_back(i + '0');
        }
        cout << name << "\t\t\t\t";
        for(int j=0; j<distanceMatrix.size(); j++){
            cout << distanceMatrix[i][j] <<  "\t\t\t";
        }
        cout << endl;
    }
}


unordered_map<string, vector<int>> BikeRebalancingModel::analyzeOptimalRoute(vector<int> optimalRoute){
    unordered_map<string, vector<int>> distribution;
    vector<int> route;
    int tripsCount =0;
    int totalDistance = 0;
    for(int v; v < vehicles.size(); v++){
        Vehicle currentV = vehicles[v];
        route.push_back(0);
        tripsCount=0;
        totalDistance=0;
        int availableCapacity = currentV.getCapacity();
        for(int i=0; i < optimalRoute.size(); i++){
            int stationCapacity = stations[optimalRoute[i]-1].getDemand();
            if(availableCapacity - stationCapacity >= 0){
                route.push_back(optimalRoute[i]);
                auto indexOf = find(route.begin(), route.end(), optimalRoute[i]);
                indexOf--;
                //totalDistance+=distanceMatrix[route.get(route.indexOf(optimalRoute[i])-1)][optimalRoute[i]];
                totalDistance+=distanceMatrix[*indexOf][optimalRoute[i]];
                availableCapacity = availableCapacity - stationCapacity;
            }
            else {
                tripsCount++;
                availableCapacity = vehicles[v].getCapacity();
                route.push_back(0);
                totalDistance+=distanceMatrix[optimalRoute[i-1]][0];
                i--;
            }
        }
        route.push_back(0);
        tripsCount++;
        string key = "VehicleCap:"+ to_string(vehicles[v].getCapacity()) + ",Trips:" + to_string(tripsCount) + ",TotalDistance:" + to_string(totalDistance);
        distribution[key] = route;
    }
    return distribution;

}

int BikeRebalancingModel::getNOfStations() const {
    return nOfStations;
}

int BikeRebalancingModel::getNOfVehicles() const {
    return nOfVehicles;
}

const vector<vector<double>> &BikeRebalancingModel::getDistanceMatrix() const {
    return distanceMatrix;
}

const vector<Station> &BikeRebalancingModel::getStations() const {
    return stations;
}

const vector<Vehicle> &BikeRebalancingModel::getVehicles() const {
    return vehicles;
}
