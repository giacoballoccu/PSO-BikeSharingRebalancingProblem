//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include <iomanip>
#include <fstream>
#include "BikeRebalancingModel.h"
#include "stdio.h"
#include "iostream"

BikeRebalancingModel::BikeRebalancingModel(string filename) {
    ifstream file;
    file.open(filename);
    if (!file)
        throw runtime_error("File not found!");
    file >> nOfStations;
    int demandValue;
    vector<Station> stations;
    for (int i = 0; i < nOfStations; i++) {
        file >> demandValue;
        stations.push_back(Station(demandValue));
    }
    stations.front() = Station(0), stations.back() = Station(0); //Setting depots
    BikeRebalancingModel::stations = stations;
    int vehicleCapacity;
    file >> vehicleCapacity;
    nOfVehicles = 2;
    for (int i = 0; i < nOfVehicles; i++) {
        vehicles.push_back(Vehicle(vehicleCapacity));
    }
    distanceMatrix = vector<vector<double>>(nOfStations, vector<double>(nOfStations, 0));
    for (int r = 0; r < distanceMatrix.size(); r++) {
        for (int c = 0; c < distanceMatrix.size(); c++) {
            file >> distanceMatrix[r][c];
        }
    }
    nOfStations -= 2; //Fix number of stations excluding depots
}

BikeRebalancingModel::BikeRebalancingModel(int nStations, vector<int> vehicleCapacity, int nVehicles, int msd) {
    nOfStations = nStations;
    nOfVehicles = nVehicles;
    distanceMatrix = vector<vector<double>>(nStations + 2, vector<double>(nStations + 2, 0));
    stations = vector<Station>(nStations + 2, Station());
    vehicles = vector<Vehicle>(nVehicles, Vehicle());


    for (int i = 0; i < nOfStations + 2; i++) {
        int demand;
        (i == 0 or i == nOfStations + 1) ? demand = 0 : demand = getRandomDemand(msd);
        stations[i] = Station(demand);
    }
    //calculate distance between stations
    for (int i = 0; i < stations.size(); i++) {
        for (int j = i; j < stations.size(); j++) {
            if (i == j)
                distanceMatrix[i][j] = 0;
            else
                distanceMatrix[i][j] = distanceMatrix[j][i] = stations[i].getDistanceFrom(stations[j]);
        }
    }
    //initialize capacity of each Vehicle
    for (int i = 0; i < nOfVehicles; i++) {
        vehicles[i] = Vehicle(vehicleCapacity[i]);
    }
}

void BikeRebalancingModel::printModelDetails() {
    cout << "No Of Stations : " << nOfStations << endl;
    cout << "Stations Details : " << endl;
    for (int i = 0; i < stations.size(); i++) {
        if (i == 0) { cout << "Starting "; }
        if (i == stations.size() - 1) { cout << "Ending "; }
        cout << stations[i] << " " << endl;
    }
    cout << "\n";
    cout << "No Of Vehicles : " << nOfVehicles << endl;
    for (Vehicle v: vehicles)
        cout << v << endl;
    cout << "\n";
    cout << "Distance Matrix : \n";
    cout << "\t\t\tDepot\t";
    for (int k = 0; k < stations.size() - 2; k++)
        cout << "Stat" << (k + 1) << "\t";
    cout << "Depot";
    cout << endl;

    for (int i = 0; i < distanceMatrix.size(); i++) {
        string name;
        if (i == 0 or i == distanceMatrix.size() - 1) {
            name = "Depot\t";
        } else {
            name = "Station" + to_string(i);
        }
        cout << name << "\t";

        for (int j = 0; j < distanceMatrix.size(); j++) {
            cout << distanceMatrix[i][j] << " \t";
        }
        cout << endl;
    }
}


unordered_map<string, vector<int>> BikeRebalancingModel::analyzeOptimalRoute(vector<int> optimalRoute) {
    unordered_map<string, vector<int>> distribution;
    vector<int> route;
    int tripsCount = 0;
    int totalDistance = 0;
    for (int v = 0; v < vehicles.size(); v++) {
        Vehicle currentV = vehicles[v];
        route.push_back(0);
        tripsCount = 0;
        totalDistance = 0;
        int availableCapacity = currentV.getCapacity();
        for (int i = 0; i < optimalRoute.size(); i++) {
            int stationCapacity = stations[optimalRoute[i] - 1].getDemand();
            if (stationCapacity < 0) { // Dropoff node
                if (availableCapacity - stationCapacity >= 0) {
                    route.push_back(optimalRoute[i]);
                    auto indexOf = find(route.begin(), route.end(), optimalRoute[i]);
                    indexOf--;
                    //totalDistance+=distanceMatrix[route.get(route.indexOf(optimalRoute[i])-1)][optimalRoute[i]];
                    totalDistance += distanceMatrix[*indexOf][optimalRoute[i]];
                    availableCapacity = availableCapacity - stationCapacity;
                } else {
                    tripsCount++;
                    availableCapacity = vehicles[v].getCapacity();
                    route.push_back(0);
                    totalDistance += distanceMatrix[optimalRoute[i - 1]][0];
                    i--;
                }
            } else if (stationCapacity < 0) {

            } else {
                continue;
            }
        }
        route.push_back(0);
        tripsCount++;
        string key = "VehicleCap:" + to_string(vehicles[v].getCapacity()) + ",Trips:" + to_string(tripsCount) +
                     ",TotalDistance:" + to_string(totalDistance);
        distribution[key] = route;
    }
    return distribution;

}


unordered_map<string, vector<int>> BikeRebalancingModel::analyzeOptimalRouteSimultaneous(vector<int> optimalRoute) {
    unordered_map<string, vector<int>> distribution;
    vector<int> route;
    int tripsCount = 0;
    int totalDistance = 0;
    for (int v = 0; v < nOfVehicles; v++) {
        route.push_back(0);
        tripsCount = 0;
        totalDistance = 0;
        int availableCapacity = vehicles[v].getCapacity() / 2;
        int maxCapacity = vehicles[v].getCapacity();
        for (int i = 0; i < optimalRoute.size(); i++) {
            int stationDemand = stations[optimalRoute[i]].getDemand();
            bool isPickupNode = stationDemand < 0;

            if (stationDemand == 0) continue; // Station is already balance
            /*The station need more bike than the vehicle have, the vehicle takes the ones that can take
             * and go to the deposit for fullfill his capacity with extra bikes */
            if (availableCapacity - stationDemand < 0) {
                int residualCapacity = maxCapacity - availableCapacity;
                stations[i].setDemand(stationDemand - residualCapacity);
                availableCapacity = maxCapacity;
                tripsCount++;
                route.push_back(optimalRoute[i]);
                route.push_back(optimalRoute[i]);
                route.push_back(0);
                route.push_back(0);
                totalDistance += distanceMatrix[optimalRoute[i]][0];
                i--;
                continue;
                /*The station has more bike than the maximum amount the vehicle can carry, the vehicle takes the ones
                 * that can take and go to the deposit to empty his capacity*/
            } else if (availableCapacity - stationDemand > maxCapacity) {
                int residualCapacity = maxCapacity - availableCapacity;
                stations[i].setDemand(stationDemand + residualCapacity);
                tripsCount++;
                availableCapacity = 0;
                route.push_back(optimalRoute[i]);
                route.push_back(optimalRoute[i]);
                route.push_back(0);
                route.push_back(0);
                totalDistance += distanceMatrix[optimalRoute[i]][0];
                i--;
                continue;
            }
            availableCapacity -= stationDemand;
            route.push_back(optimalRoute[i]);
            route.push_back(optimalRoute[i]);
            auto indexOf = find(route.begin(), route.end(), optimalRoute[i]);
            indexOf--;
            totalDistance += distanceMatrix[*indexOf][optimalRoute[i]];
        }
        route.push_back(nOfStations + 1);
        tripsCount++;
        string key = "VehicleCap:" + to_string(vehicles[v].getCapacity()) + ",Trips:" + to_string(tripsCount) +
                     ",TotalDistance:" + to_string(totalDistance);
        distribution[key] = route;
    }
    return distribution;

}

bool BikeRebalancingModel::isProblemFeasible() {
    int Qtot = 0;
    /*Calculate total demand along nodes*/
    for (int s = 1; s < stations.size() - 1; s++) {
        Qtot += stations[s].getDemand();
    }
    /*Remove from total demand the extra bikes that can be picked up from depot*/
    Qtot -= stations[0].getDemand();
    Qtot -= stations[stations.size() - 1].getDemand();
    /*Calculate total vehicle capacity*/
    int Ctot = 0;
    for (Vehicle v : vehicles) {
        Ctot += v.getCapacity();
    }

    return Ctot >= Qtot;
}

int BikeRebalancingModel::getRandomDemand(const int max) const {
    bool positive = rand() > (RAND_MAX / 2);
    int demand = rand() % max + 1;
    return positive ? demand : -demand;
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
