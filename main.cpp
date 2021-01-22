
#include "BikeSharingRebalancingModel/Simulator.h"


int main(int argc, char *argv[])
{
    Simulator *sim = new Simulator();
    //sim->start("../Dataset/21Ottawa30.txt");
    sim->start();
    delete(sim);
    return 0;
}
