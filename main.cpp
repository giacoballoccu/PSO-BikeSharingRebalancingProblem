
#include "BikeSharingRebalancingModel/Simulator.h"


int main(int argc, char *argv[])
{
    Simulator *sim = new Simulator();
    sim->start();
    //mainWindow.show();
    delete(sim);
    return 0;
}
