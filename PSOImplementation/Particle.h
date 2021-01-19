//
// Created by Giacomo Balloccu on 18/01/2021.
//

#ifndef BIKEREDISTRIBUTIONHEURISTIC_PARTICLE_H
#define BIKEREDISTRIBUTIONHEURISTIC_PARTICLE_H
#include <vector>
#include "stdio.h"
#include "iostream"
#include "PSOUtils.h"
using namespace std;

class Particle {
private:
    vector<double> xSolution;

    double xFitnessValue;

    vector<double> pVelocity;
    vector<double> pBestVelocity;

    vector<double> pBest;
    double pBestValue;
public:
    Particle(){};
    Particle(vector<int> x){
            xSolution = PSOutils::copyVecIntToVecDouble(x);
            pBest = xSolution;
            initializeRandomVelocities(xSolution.size());
            pBestVelocity = pVelocity;
        }

    void initializeRandomVelocities(int n);

    double getRandomVelocity(int ub);

    const vector<double> &getXSolution() const;

    double getXFitnessValue() const;

    const vector<double> &getPVelocity() const;

    const vector<double> &getPBestVelocity() const;

    const vector<double> &getPBest() const;

    double getPBestValue() const;

    void setPBestValue(double pBestValue){
        Particle::pBestValue = pBestValue;
    }

    void setXFitnessValue(double xFitnessValue){
        Particle::xFitnessValue = xFitnessValue;
    }
    void setPBest(vector<double> pBest){
        Particle::pBest = pBest;
    }
    void setPBestVelocity(vector<double> pBestVelocity){
        Particle::pBestVelocity = pBestVelocity;
    }
    void setPVelocity(vector<double> pVelocity){
        Particle::pVelocity = pVelocity;
    }
    void setXSolution(vector<double> xSolution){
        Particle::xSolution = xSolution;
    }
};
ostream& operator<<(ostream& os, const Particle& p);

#endif //BIKEREDISTRIBUTIONHEURISTIC_PARTICLE_H
