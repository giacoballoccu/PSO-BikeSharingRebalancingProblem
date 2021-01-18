//
// Created by Giacomo Balloccu on 18/01/2021.
//

#include "Particle.h"
/*Populate the velocities vector with n random velocities*/
void Particle::initializeRandomVelocities(int n) {
    pVelocity = vector<double>(n);
    for (int i = 0; i < n; i++) {
        pVelocity[i] = getRandomVelocity(n);
    }
}

/*Get random velocity in a range upper bound lower bound*/
double Particle::getRandomVelocity(int upperBound) {
    int lowerBound = 0;
    double n = (double)rand() / RAND_MAX;
    return lowerBound + n * (upperBound - lowerBound);
}

ostream& operator<<(ostream& os, const Particle& p)
{
    os << "Particle [xSolution=" + PSOutils::doubleVectorToString(p.getXSolution()) + ", xFitnessValue=" + to_string(p.getXFitnessValue()) + ", pBest="
          + PSOutils::doubleVectorToString(p.getPBest()) + ", pBestValue=" + to_string(p.getPBestValue()) + ", pVelocity=" + PSOutils::doubleVectorToString(p.getPVelocity())
          + "]";
    return os;
}



const vector<double> &Particle::getXSolution() const {
    return xSolution;
}

double Particle::getXFitnessValue() const {
    return xFitnessValue;
}

const vector<double> &Particle::getPVelocity() const {
    return pVelocity;
}

const vector<double> &Particle::getPBestVelocity() const {
    return pBestVelocity;
}

const vector<double> &Particle::getPBest() const {
    return pBest;
}

double Particle::getPBestValue() const {
    return pBestValue;
}
