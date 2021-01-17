//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "Station.h"
#include "iostream"
using namespace std;
const string Station::to_string() const {
    cout << "Store [demand=" << getDemand() << "]";
};
ostream& operator<<(ostream& os, const Station& s)
{
    os << "Store [demand=" << s.getDemand() << "]";
    return os;
}