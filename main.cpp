#include <iostream>
#include <iomanip>

#include "Data.h"
#include "Interface.h"
int main() {
    Data d;
    bool a = d.readStations("../Data/Project1Data/stations.csv");
    bool b = d.readNetworks("../Data/Project1Data/network.csv");
    d.findTrainSources();
    cout << endl << a << endl;
    cout << b << endl;
    cout << d.getMaxFlow(2,6);
    cout << "\n\n";

    cout << "Done";
    Interface iFace = Interface();
    iFace.setData(d);
    try {
        iFace.welcomePage();
    }
    catch (int exit) {
        return 0;
    }

    return 0;
}
