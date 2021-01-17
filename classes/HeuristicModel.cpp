//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "HeuristicModel.h"
#include "stdio.h"
#include "iostream"
void HeuristicModel::printModelDetails(){

    cout << "No Of Stores : " << noOfStations << endl;
    cout << "Store Details : ";
    for(Station s: stations)
        cout << s << " ";
    cout << "\n";
    cout << "No Of Vehicles : "  << noOfVehicles << endl;
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
        if(i == 0 or i == noOfStations){
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