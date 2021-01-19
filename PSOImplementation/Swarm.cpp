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

void Swarm::printSwarmDetails(){


    cout << "\nNo of Particles : " << particles.size();


    cout << "\nParticle Details : ";
    for(Particle p: particles)
        cout << "\n" << p;

    cout << "\n" << "Global   [gBest=" << PSOutils::doubleVectorToString(globalBest) << ", gFitnessValue=" << globalFitnessValue << "]";
}

void Swarm::printIterationResults(int t, unordered_map<string, unordered_map<double, double>> particleProgress){
    cout << t << " \t\t";
    int pNo = 1;
    for(Particle p: particles){
        string key = "p" + to_string(pNo);
        if(particleProgress.count(key) == 0)
            particleProgress[key] = unordered_map<double, double>();
        pair<double,double> toinsert(t, p.getPBestValue());
        particleProgress[key].insert(toinsert);
        cout << to_string(p.getXFitnessValue()) + "\t" + to_string(p.getPBestValue()) + "\t\t";
        pNo++;
    }
    cout << to_string(globalFitnessValue) << "\n";
}

void Swarm::optimizeSolutions(){

    for(Particle p: particles){

        // find the new velocity
        updateVelocity(p);

        // find new solution
        updateSolution(p);

        // update the fitness value of the particles
        p.setXFitnessValue(generateFitnessValue(p.getXSolution()));

        // update pBest of the particle
        if(p.getXFitnessValue() < p.getPBestValue()){
            p.setPBest(p.getXSolution());
            p.setPBestValue(p.getXFitnessValue());
            p.setPBestVelocity(p.getPVelocity());
        }

    }

    //update the gBest after this one iteration
    findGlobalBest();


}

void Swarm::updateVelocity(Particle p){

    double w = 0.6;

    double o1 = 0.2;
    double b1 = 0.3;

    double o2 = 0.2;
    double b2 = 0.5;

    vector<double> newV = vector<double>(p.getPVelocity().size());

    for(int i=0; i<newV.size(); i++){
        newV[i] = w*p.getPVelocity()[i] + (o1*b1*(p.getPBest()[i]-p.getXSolution()[i])) + (o2*b2*(globalBest[i] - p.getXSolution()[i]));
    }

    p.setPVelocity(newV);

}

void Swarm::updateSolution(Particle p){
    vector<double> newXSolution = vector<double>(p.getXSolution().size());

    for(int i=0; i<p.getXSolution().size(); i++){
        newXSolution[i] = p.getXSolution()[i] + p.getPVelocity()[i] > p.getXSolution().size() ? p.getXSolution().size() : p.getXSolution()[i] + p.getPVelocity()[i];
    }
    p.setXSolution(newXSolution);

}

vector<int> Swarm::decodeOptimalSolution(){

    cout << "gFitnessValue=" << globalFitnessValue << endl;
    cout << "gBest=" << PSOutils::doubleVectorToString(globalBest);

    unordered_map<double, vector<int>> indicies;

    for(int i=0; i<globalBest.size() ; i++){
        if(indicies.find(globalBest[i]) == indicies.end())
            indicies[globalBest[i]].push_back(i);
    }

    sort(globalBest.begin(), globalBest.end());

    vector<int> optimalRoute = vector<int>(globalBest.size());

    for(int i=0; i<optimalRoute.size(); i++){
        if(indicies[globalBest[i]].size() > 1){
            // find the lowest velocity and add that first
            int ii = i;
            for(int k=0; k<indicies[globalBest[ii]].size(); k++){
                optimalRoute[i] = indicies[globalBest[ii]][k] + 1;
                i++;
            }

        }else
            optimalRoute[i] = indicies[globalBest[i]][0] + 1;
    }

    return optimalRoute;
}
