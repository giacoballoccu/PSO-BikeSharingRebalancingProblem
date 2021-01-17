
#include "classes/HeuristicModel.h"
int main() {
    int nStations = 6, nVehicles = 2, msd = 100, msr = 10;
    vector<int> vehicleCapacity = vector<int>(2, 10);
    HeuristicModel * model = new HeuristicModel(nStations, vehicleCapacity, nVehicles, msd, msr);
    model->printModelDetails();
    model->analyzeOptimalRoute();
    delete(model);
    return 0;
}
