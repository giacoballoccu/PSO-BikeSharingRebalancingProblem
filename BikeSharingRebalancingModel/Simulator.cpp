#include "Simulator.h"
#include "BikeSharingRebalancingModel/BikeRebalancingModel.h"
#include "PSOImplementation/Swarm.h"
#include <iostream>
#include <fstream>
#include <string>
Simulator::Simulator(){};


int Simulator::start() {
    vector<int> vehicleCapacity = vector<int>(noOfVehicles, 10);
    //model->analyzeOptimalRoute();
    std::ofstream out("../Results/test1.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


    cout << "---------------------------------------------------------";
    cout << "Bike Rebalacing Model";
    cout << "---------------------------------------------------------";

    //Design the distribution model for the problem
    BikeRebalancingModel brm = BikeRebalancingModel(noOfStations, vehicleCapacity, noOfVehicles, MAXIMUM_STATION_DEMAND, MAXIMUM_STATION_OFFERT);
    brm.printModelDetails();
    cout << "---------------------------------------------------------" << endl;

    cout << "Swarm Model";
    cout << "---------------------------------------------------------" << endl;
    //Initialize the swarm for the distribution model
    Swarm swarm = Swarm(brm, noOfStations);
    swarm.printSwarmDetails();
    cout << "---------------------------------------------------------" << endl;

    cout << "Iterations Details" << endl;
    cout << "---------------------------------------------------------" << endl;
    unordered_map<string, unordered_map<double, double>> particleProgress;

    //print iteration 0 results
    cout << "Iteration\t";
    for(int i=0; i<swarm.getParticles().size(); i++)
        cout << "f(x:"+ to_string(i+1) + ") f(pBest:"+ to_string(i+1) + ")\t";

    cout << "f(gBest)" << endl;
    swarm.printIterationResults(0, particleProgress);


    //Optimize the solution and return the best solution after the iterations terminate
    for(int t=1; t<=N_ITERATIONS;t++){
        swarm.optimizeSolutions();
        swarm.printIterationResults(t, particleProgress);
    }
    cout << endl << "---------------------------------------------------------" << endl;

    cout << "Decode gBest Solution\n";
    cout << "---------------------------------------------------------" << endl;
    //Decode the gBest Solution
    vector<int> optimalRoute =  swarm.decodeOptimalSolution();
    cout << "Optimal Route : " << PSOutils::intVectorToString(optimalRoute);
    //cout << "Decoding the best solution..." << endl;
    string answer;
    //cin >> answer;
    if(true){
        cout << "Decode gBest Solution" << endl;
        cout << "---------------------------------------------------------" << endl;
        //Decode the gBest Solution
        vector<int> optimalRoute =  swarm.decodeOptimalSolution();
        cout << "Optimal Route : " << PSOutils::intVectorToString(optimalRoute);

        cout << "---------------------------------------------------------" << endl;
        //Print analysis for optimal route for the distribution model
        cout << "Analysis of Optimal Route for dropOff Only: " << endl;
        cout << "---------------------------------------------------------" << endl;
        //GraphWidget *gui = new GraphWidget();
        unordered_map<string, vector<int>> distributionMap =  brm.analyzeOptimalRoute(optimalRoute);

        for (auto [k,v] : distributionMap) {
           cout << k + " -> " + PSOutils::intVectorToString(v) << endl;
           //gui.displayGraph("Graph"+k, v);
        }

        cout << "---------------------------------------------------------" << endl;
        cout << "Analysis of Optimal Route for simultaneously pickup and dropOff: " << endl;
        cout << "---------------------------------------------------------" << endl;
        distributionMap = brm.analyzeOptimalRouteSimultaneous(optimalRoute);
        for (auto [k,v] : distributionMap) {
            cout << k + " -> " + PSOutils::intVectorToString(v) << endl;
        }

   }

    return 0;
}


