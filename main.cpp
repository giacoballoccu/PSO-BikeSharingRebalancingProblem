
#include "classes/BikeRebalancingModel.h"
#include "PSO/Swarm.h"

int main() {
    int noOfStations = 7, noOfVehicles = 1;
    int MAXIMUM_STATION_DEMAND = 30, MINIMUM_STATION_DEMAND = -10;
    int N_PARTICLES = 3, N_ITERATIONS = 12;
    vector<int> vehicleCapacity = vector<int>(noOfVehicles, 10);
    BikeRebalancingModel * model = new BikeRebalancingModel(noOfStations, vehicleCapacity, noOfVehicles, MAXIMUM_STATION_DEMAND, MINIMUM_STATION_DEMAND);
    model->printModelDetails();
    //model->analyzeOptimalRoute();

    cout << "---------------------------------------------------------";
    cout << "Bike Rebalacing Model";
    cout << "---------------------------------------------------------";

    //Design the distribution model for the problem
    BikeRebalancingModel brm = BikeRebalancingModel(noOfStations, vehicleCapacity, noOfVehicles, MAXIMUM_STATION_DEMAND, MINIMUM_STATION_DEMAND);
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
        cout << "f(x:"+ to_string(i+1) + ")\t f(pBest:"+ to_string(i+1) + ")\t\t\t";

    cout << "f(gBest)" << endl;
    swarm.printIterationResults(0, particleProgress);


    //Optimize the solution and return the best solution after the iterations terminate
    for(int t=1; t<=N_ITERATIONS;t++){
        swarm.optimizeSolutions();
        swarm.printIterationResults(t, particleProgress);
    }
    cout << "\n---------------------------------------------------------";

    cout << "Decode gBest Solution\n";
    cout << "---------------------------------------------------------";
    //Decode the gBest Solution
    vector<int> optimalRoute =  swarm.decodeOptimalSolution();
    cout << "Optimal Route : " << PSOutils::intVectorToString(optimalRoute);

    delete(model);
    return 0;
}
