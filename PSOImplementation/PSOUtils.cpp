#include <string>
#include <sstream>
#include <iomanip>
#include "PSOUtils.h"
namespace PSOutils{
    /*Convert vector of double into a string useful to cout the results*/
    string PSOutils::doubleVectorToString(vector<double> vec) {
        ostringstream os;
        os << setprecision(1) << fixed;
        for(double x : vec){
            os << x << " ";
        }
        return os.str();
    }
    string PSOutils::intVectorToString(vector<int> vec) {
        string ans;
        for(int x : vec){
            ans += to_string(x);
            ans += ' ';
        }
        return ans;
    }
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    void PSOutils::KnuthShuffle(vector<int>& arr){
        /* initialize random seed: */
        for (int i = arr.size() - 1; i > 0; i--){
            int index = rand() % i;
            swap(arr[index], arr[i]);
        }
    }
    /*Convert an input vector of int in a vector of double */
    vector<double> PSOutils::copyVecIntToVecDouble(const vector<int> vec) {
        vector<double> ans;
        for(int val : vec) {
            ans.push_back(double(val));
        }
        return ans;
    }
    vector<int> PSOutils::copyVecDoubleToVecInt(const vector<double> vec){
        vector<int> ans;
        for(int val : vec) {
            ans.push_back(int(val));
        }
        return ans;
    }


}

