# PSO-BikeSharingRebalancingProblem
An implementation of the Particle Swarm Optimization method applied to the specific problem of Bike Sharing Redistribution
# Usage
- Clone the project
- Open with your favorite ide
- Choose if you want to read from file or with hard given data
  - For the former, insert the pathfile as argument for the Simulator.start(pathname) function. (Pay attention to txt format, check a txt from the Dataset folder).
  - For the latter, you can manually set your parameters from the Simulator.h
- Run the code to generate the log file with the optimal solution found and its analysis. This step also create txt files for visualizing the result.
- If you want to visualize the result you can run from terminal python GraphVisualizer.py
# Problem Definition
The problem is a particular instance of the Capacitated Vehicle Routing Problem. After a whole day of people using the BikeSharing-System bikes are distributed all over stations, causing some stations to have a low amount of bikes or a too-high amount. So our vehicles need to pick up or drop off bikes in stations making them balanced.  
The model is composed by Stations which can have a positive demand (Dropoff node) or negative demand (Pickup node), a station is balanced when his demand is equal to 0. The vehicles have a maximum amount of bikes that can carry (Capacity), if the vehicle is too full or too empty to fulfill the need of a station he can always go back to the deposit and recharge or empty his capacity.
# Proposed Solution
The goal of the system is to define a single path between S stations from the Starting Depot, so that K vehicles with L capacity minimizing the distance traveled by our vehicles while rebalancing every station. This is done to reduce the economic and ecological cost of the rebalancing. In the particular instance of the problem here implemented the vehicle when has finished needs to reach the Ending Depot.  
Since Bike Sharing Redistribution is a NP-Hard Problem and standard solvers like CPLEX require an incredible amount of time and ram to solve it (as you can see in my previous work https://github.com/giacoballoccu/Bike-sharing-rebalancing-problem). I have implemented this version which use PSO to obtain a good result in a small amount of time. Also is possible to run every txt in dataset, even the bigger and obtain a good result in a resonable amount of time. This is obtained thanks to the mix of speed from C++ and an Euristic fitness function.
