
#include "BikeSharingRebalancingModel/Simulator.h"


int main(int argc, char *argv[])
{
    srand (time(NULL));
    Simulator *sim = new Simulator();
    string filename = "16LaSpezia30.txt";
    sim->start("../Dataset/" + filename, filename);
    //sim->start();
    delete(sim);
    return 0;
}
