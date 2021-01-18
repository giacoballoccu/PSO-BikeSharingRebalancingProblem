//
// Created by Giacomo Balloccu on 17/01/2021.
//

#include "Station.h"
#include "iostream"
using namespace std;

ostream& operator<<(ostream& os, const Station& s)
{
    os << "Store [demand=" << s.getDemand() << "]";
    return os;
}