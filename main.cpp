
#include "BikeSharingRebalancingModel/Simulator.h"


int main(int argc, char *argv[])
{
    Simulator *sim = new Simulator();
    string filename = "3Bari10.txt";
    sim->start("../Dataset/" + filename, filename);
    //sim->start();
    delete(sim);
    return 0;
}
