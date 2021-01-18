//
// Created by Giacomo Balloccu on 18/01/2021.
//

#include <string>
#include "Utils.h"
namespace Utils{
    string Utils::doubleVectorToString(vector<double> vec) {
        string ans;
        for(double x : vec){
            ans += to_string(x);
            ans += ' ';
        }
        return ans;
    }
}
