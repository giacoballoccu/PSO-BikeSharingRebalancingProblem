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
#include "Particle.h"
#include "../classes/BikeRebalancingModel.h"


using namespace std;

class Swarm {
    vector<Particle> particles;
    vector<vector<double>> distanceMatrix;
    vector<double> globalBest;
    vector<double> globalBestVelocities;
    double globalFitnessValue;
public:
    Swarm(BikeRebalancingModel hm, int nOfParticles){
        distanceMatrix = hm.getDistanceMatrix();

        int solutionLength = hm.getNOfStations();

        // define the possible solution scope
        vector<int> possibleSolution;

        //Check if it's better to initialize or pb
        for(int i=0; i<solutionLength; i++){
            possibleSolution.push_back(i+1);
        }

        // initialize the Swarm Particles
        particles = vector<Particle>(nOfParticles, Particle());

        for(int i=0; i<nOfParticles; i++){
            PSOutils::KnuthShuffle(possibleSolution);
            particles[i] = Particle(possibleSolution);
            particles[i].setXFitnessValue(generateFitnessValue(particles[i].getXSolution()));
            particles[i].setPBestValue(generateFitnessValue(particles[i].getPBest()));
        }

        //find global best
        globalBest = vector<double>(solutionLength);
        globalBestVelocities = vector<double>(solutionLength);
        globalFitnessValue = DBL_MAX;
        findGlobalBest();

    }
    double generateFitnessValue(vector<double> currentSolution);
    void findGlobalBest();
    void optimizeSolutions();
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
