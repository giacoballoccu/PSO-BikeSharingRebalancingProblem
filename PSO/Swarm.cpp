//
// Created by Giacomo Balloccu on 18/01/2021.
//

#include "Swarm.h"
/*Need to be adapted according to problem F4 starting and end depot*/
double Swarm::generateFitnessValue(vector<double> currentSolution){

    int prevStation = 0; // since we will be starting from the depot which has node 0
    double fitnessSum = 0;

    //return the value of objective function
    for(int i=0; i<currentSolution.size(); i++){
        int v = (int)round(currentSolution[i]);
        fitnessSum += distanceMatrix[prevStation][v];
        prevStation = v;
    }

    fitnessSum += distanceMatrix[prevStation][0]; // add distance back to the depot

    return fitnessSum;
}

void Swarm::findGlobalBest(){
    for(Particle p: particles){
        double currentXFitnessValue = p.getXFitnessValue();
        if(currentXFitnessValue < globalFitnessValue){
            globalFitnessValue = currentXFitnessValue;
            globalBest = p.getPBest();
            globalBestVelocities = p.getPBestVelocity();
        }
    }
}