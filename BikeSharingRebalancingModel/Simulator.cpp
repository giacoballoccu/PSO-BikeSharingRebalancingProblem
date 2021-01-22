#include "Simulator.h"
#include "BikeSharingRebalancingModel/BikeRebalancingModel.h"
#include "PSOImplementation/Swarm.h"
#include <iostream>
#include <fstream>
#include <string>
Simulator::Simulator(){};

int Simulator::start(string filename) {
    //Design the distribution model for the problem, if the simulator is called with a file construct from it
    BikeRebalancingModel brm = (filename == "")
                               ? BikeRebalancingModel(noOfStations, vehicleCapacity, noOfVehicles, MAXIMUM_STATION_DEMAND)
                               : BikeRebalancingModel(filename);
    noOfStations = brm.getNOfStations();
    noOfVehicles = brm.getNOfVehicles();

    /*Setup logger to file*/
    cout << setprecision(1) << fixed;
    string logname = to_string(noOfStations) + "Stations" + to_string(noOfVehicles) + "Vehicles" + to_string(vehicleCapacity[0]) + "Capacity" + ".txt";
    std::ofstream out("../Results/" + logname);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    cout << "---------------------------------------------------------" << "\n";
    cout << "Bike Rebalacing Model" << "\n";
    cout << "---------------------------------------------------------" << "\n";

    brm.printModelDetails();
    bool isFeasible = brm.isProblemFeasible();
    cout << "Is problem feasible? " << (isFeasible ? "Yes" : "No") << endl;
    if(!isFeasible) return 0;
    cout << "---------------------------------------------------------" << "\n";
    cout << "Swarm Model" << "\n";
    cout << "---------------------------------------------------------" << "\n";
    //Initialize the swarm for the distribution model
    Swarm swarm = Swarm(brm, N_PARTICLES);
    swarm.printSwarmDetails();
    cout << "---------------------------------------------------------" << "\n";
    cout << "Iterations Details" << "\n";
    cout << "---------------------------------------------------------" << "\n";
    unordered_map<string, unordered_map<double, double>> particleProgress;

    //print iteration 0 results
    cout << "Iteration\t";
    for(int i=0; i<swarm.getParticles().size(); i++)
        cout << "f(x:"+ to_string(i+1) + ") f(pBest:"+ to_string(i+1) + ")\t";

    cout << "f(gBest)" << "\n";
    swarm.printIterationResults(0, particleProgress);


    //Optimize the solution and return the best solution after the iterations terminate
    for(int t=1; t<=N_ITERATIONS;t++){
        swarm.optimizeSolutions(brm);
        swarm.printIterationResults(t, particleProgress);
    }
    //Decode the gBest Solution
    cout << "---------------------------------------------------------" << "\n";
    cout << "Decode gBest Solution" << "\n";
    cout << "---------------------------------------------------------" << "\n";
    //Decode the gBest Solution
    vector<int> optimalRoute =  swarm.decodeOptimalSolution();
    cout << "Optimal Route : " << "0 " << PSOutils::intVectorToString(optimalRoute) << noOfStations+1 << "\n";

    cout << "---------------------------------------------------------" << "\n";
    cout << "Analysis of Optimal Route for simultaneously pickup and dropOff: " << "\n";
    cout << "---------------------------------------------------------" << "\n";
    unordered_map<string, vector<int>> distributionMap = brm.analyzeOptimalRouteSimultaneous(optimalRoute);
    for (auto [k,v] : distributionMap) {
        cout << k << " -> " << PSOutils::intVectorToString(v) << "\n";
    }

    /*Save data into a txt to load and visualize with python*/
    ofstream outdata;
    remove("../GraphVisualizer/.nodes.txt");
    outdata.open("../GraphVisualizer/.nodes.txt");
    for(Station s : brm.getStations()){
        outdata << to_string(s.getDemand()) << " " << to_string(s.getCoordinates().first)  << " " << to_string(s.getCoordinates().second) << "\n";
    }
    outdata.close();
    remove("../GraphVisualizer/.edges.txt");
    outdata.open("../GraphVisualizer/.edges.txt");
    for (auto [k,v] : distributionMap) {
        outdata << PSOutils::intVectorToString(v) << "\n";
    }
    outdata.close();
    return 0;
}

void Simulator::readFromDataset(string path){

}

