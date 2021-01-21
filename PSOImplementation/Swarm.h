//
// Created by Giacomo Balloccu on 18/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_SWARM_H
#define BIKEREDISTRIBUTIONHEURISTIC_SWARM_H
#include <vector>
#include <float.h>
#include "stdio.h"
#include "iostream"
#include "math.h"
#include "PSOImplementation/Particle.h"
#include "BikeSharingRebalancingModel/BikeRebalancingModel.h"


using namespace std;

class Swarm {
    vector<Particle> particles;
    vector<vector<double>> distanceMatrix;
    vector<double> globalBest;
    vector<double> globalBestVelocities;
    double globalFitnessValue;
public:
    Swarm(BikeRebalancingModel hm, int nOfParticles);
    double generateFitnessValue(vector<double> currentSolution, BikeRebalancingModel& brm);
    void findGlobalBest();
    void optimizeSolutions(BikeRebalancingModel& brm);
    vector<int> decodeOptimalSolution();
    void updateVelocity(Particle p);
    void updateSolution(Particle p);
    void printSwarmDetails();
    void printIterationResults(int t, unordered_map<string, unordered_map<double, double>> particleProgress);
    vector<Particle>& getParticles(){
        return particles;
    }
};


#endif //BIKEREDISTRIBUTIONHEURISTIC_SWARM_H
