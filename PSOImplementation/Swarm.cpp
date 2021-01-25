//
// Created by Giacomo Balloccu on 18/01/2021.
//

#include <iomanip>
#include "Swarm.h"

Swarm::Swarm(BikeRebalancingModel brm, int nOfParticles) {
    distanceMatrix = brm.getDistanceMatrix();

    int solutionLength = brm.getNOfStations();

// define the possible solution scope
    vector<int> possibleSolution;

//Check if it's better to initialize or pb
    for (int i = 0; i < solutionLength; i++) {
        possibleSolution.push_back(i + 1);
    }

// initialize the Swarm Particles
    particles = vector<Particle>(nOfParticles, Particle());

    for (int i = 0; i < nOfParticles; i++) {
        PSOutils::KnuthShuffle(possibleSolution);
        particles[i] = Particle(possibleSolution);
        particles[i].setXFitnessValue(generateFitnessValue(particles[i].getXSolution(), brm));
        particles[i].setPBestValue(generateFitnessValue(particles[i].getPBest(), brm));
    }

//find global best
    globalBest = vector<double>(solutionLength);
    globalBestVelocities = vector<double>(solutionLength);
    globalFitnessValue = DBL_MAX;
    findGlobalBest();

}

/*Need to be adapted according to problem F4 starting and end depot*/
double Swarm::generateFitnessValue(vector<double> currentSolution, BikeRebalancingModel& brm) {
    int prevStation = 0; // since we will be starting from the depot which has node 0
    double fitnessSum = 0;
    vector<Station> s = brm.getStations();
    vector<Vehicle> veh = brm.getVehicles();
    int currentCapacity = 0;
    int maxCapacity = 0;
    for (Vehicle x : veh) {
        maxCapacity += x.getCapacity();
    }
    map<int, Station> pickupStations = brm.pickupStations;
    map<int, Station> dropoffStations = brm.dropoffStations;
    currentCapacity = maxCapacity;
    //return the value of objective function
    for (int i = 0; i < currentSolution.size(); i++) {
        int v = (int) round(currentSolution[i]);
        double distanceFromDepot = distanceMatrix[prevStation][0];
        int stationDemand = s[v].getDemand();
        if (stationDemand == 0) continue;
        if (currentCapacity - stationDemand < 0) {
            int bestCandidate = 0;
            double bestDistance = distanceFromDepot;
            for (int j = i + 1; j < currentSolution.size(); j++) {
                if (pickupStations.empty() or bestDistance == 0) break;
                int station_value = (int) round(currentSolution[j]);
                if (pickupStations.count(station_value) != 0) {
                    Station currentCandidate = pickupStations[station_value];
                    double distanceFromCandidate = distanceMatrix[prevStation][station_value];
                    if (currentCapacity - currentCandidate.getDemand() <= maxCapacity and distanceFromCandidate <= bestDistance) {
                        bestCandidate = j;
                        bestDistance = distanceFromCandidate;
                    }
                }
            }
            if (bestCandidate == 0) {
                //Then come back to deposit
                fitnessSum += distanceFromDepot;
                prevStation = 0;
                currentCapacity = (currentCapacity + maxCapacity/3 > maxCapacity) ? maxCapacity : currentCapacity + maxCapacity/3;
                i--;
                continue;
            } else {
                if (s[currentSolution[i]].getDemand() < 0) pickupStations[currentSolution[i]] = s[currentSolution[i]];
                swap(currentSolution[i], currentSolution[bestCandidate]);
                pickupStations.erase(currentSolution[bestCandidate]);
                i--;
                continue;
            }

        } else if (currentCapacity - stationDemand > maxCapacity) {
            int bestCandidate = 0;
            double bestDistance = distanceFromDepot;
            for (int j = i + 1; j < currentSolution.size(); j++) {
                if (dropoffStations.empty() or bestDistance == 0) break;
                int station_value = (int) round(currentSolution[j]);
                if (dropoffStations.count(station_value) != 0) {
                    Station currentCandidate = dropoffStations[station_value];
                    double distanceFromCandidate = distanceMatrix[prevStation][station_value];
                    if (currentCapacity - currentCandidate.getDemand() >= 0 and distanceFromCandidate <= bestDistance) {
                        bestCandidate = j;
                        bestDistance = distanceFromCandidate;
                    }
                }
            }
            if (bestCandidate == 0) {
                fitnessSum += distanceFromDepot;
                prevStation = 0;
                currentCapacity = (currentCapacity - maxCapacity/3 < 0) ? 0 : currentCapacity - maxCapacity/3;
                i--;
                continue;
            } else {
                if (s[currentSolution[i]].getDemand() > 0) dropoffStations[currentSolution[i]] = s[currentSolution[i]];
                swap(currentSolution[i], currentSolution[bestCandidate]);
                pickupStations.erase(currentSolution[bestCandidate]);
                i--;
                continue;
            }
        }
        currentCapacity = currentCapacity - stationDemand;
        fitnessSum += distanceMatrix[prevStation][v];
        prevStation = v;
    }

    fitnessSum += distanceMatrix[prevStation][currentSolution.size()]; // add distance back to the final depot

    return fitnessSum;
}


void Swarm::findGlobalBest() {
    for (Particle p: particles) {
        double currentXFitnessValue = p.getXFitnessValue();
        if (currentXFitnessValue < globalFitnessValue) {
            globalFitnessValue = currentXFitnessValue;
            globalBest = p.getPBest();
            globalBestVelocities = p.getPBestVelocity();
        }
    }
}

void Swarm::printSwarmDetails() {
    cout << "No of Particles : " << particles.size();


    cout << "\nParticle Details : ";
    for (Particle p: particles)
        cout << "\n" << p;

    cout << "\n" << "Global   [gBest=" << PSOutils::doubleVectorToString(globalBest) << ", gFitnessValue="
         << globalFitnessValue << "]" << endl;
}

void Swarm::printIterationResults(int t, unordered_map<string, unordered_map<double, double>> particleProgress) {
    cout << t << " \t\t\t";
    int pNo = 1;
    for (Particle p: particles) {
        string key = "p" + to_string(pNo);
        if (particleProgress.count(key) == 0)
            particleProgress[key] = unordered_map<double, double>();
        pair<double, double> toinsert(t, p.getPBestValue());
        particleProgress[key].insert(toinsert);
        cout << p.getXFitnessValue() << "\t" << p.getPBestValue() << "\t\t";
        pNo++;
    }
    cout << to_string(globalFitnessValue) << "\n";
}

void Swarm::optimizeSolutions(BikeRebalancingModel& brm) {

    for (Particle p: particles) {

        // find the new velocity
        updateVelocity(p);

        // find new solution
        updateSolution(p);

        // update the fitness value of the particles
        p.setXFitnessValue(generateFitnessValue(p.getXSolution(), brm));

        // update pBest of the particle
        if (p.getXFitnessValue() < p.getPBestValue()) {
            p.setPBest(p.getXSolution());
            p.setPBestValue(p.getXFitnessValue());
            p.setPBestVelocity(p.getPVelocity());
        }

    }

    //update the gBest after this one iteration
    findGlobalBest();


}

void Swarm::updateVelocity(Particle p) {

    double w = 0.6;

    double o1 = 0.2;
    double b1 = 0.3;

    double o2 = 0.2;
    double b2 = 0.3;

    vector<double> newV = vector<double>(p.getPVelocity().size());

    for (int i = 0; i < newV.size(); i++) {
        newV[i] = w * p.getPVelocity()[i] + (o1 * b1 * (p.getPBest()[i] - p.getXSolution()[i])) +
                  (o2 * b2 * (globalBest[i] - p.getXSolution()[i]));
    }

    p.setPVelocity(newV);

}

void Swarm::updateSolution(Particle p) {
    vector<double> newXSolution = vector<double>(p.getXSolution().size());

    for (int i = 0; i < p.getXSolution().size(); i++) {
        newXSolution[i] =
                p.getXSolution()[i] + p.getPVelocity()[i] > p.getXSolution().size() ? p.getXSolution().size() :
                p.getXSolution()[i] + p.getPVelocity()[i];
    }
    p.setXSolution(newXSolution);

}

vector<int> Swarm::decodeOptimalSolution() {

    cout << "gFitnessValue=" << globalFitnessValue << endl;
    cout << "gBest=" << PSOutils::doubleVectorToString(globalBest);

    unordered_map<double, vector<int>> indicies;

    for (int i = 0; i < globalBest.size(); i++) {
        if (indicies.find(globalBest[i]) == indicies.end())
            indicies[globalBest[i]].push_back(i);
    }

    return PSOutils::copyVecDoubleToVecInt(globalBest);
    /*sort(globalBest.begin(), globalBest.end());

    vector<int> optimalRoute = vector<int>(globalBest.size());

    for (int i = 0; i < optimalRoute.size(); i++) {
        if (indicies[globalBest[i]].size() > 1) {
            // find the lowest velocity and add that first
            int ii = i;
            for (int k = 0; k < indicies[globalBest[ii]].size(); k++) {
                optimalRoute[i] = indicies[globalBest[ii]][k] + 1;
                i++;
            }

        } else
            optimalRoute[i] = indicies[globalBest[i]][0] + 1;
    }

    return optimalRoute;*/
}
