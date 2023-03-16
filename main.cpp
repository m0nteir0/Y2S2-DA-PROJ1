#include <iostream>
#include <iomanip>

#include "Data.h"
#include "Interface.h"
int main() {
    Data d;
    bool a = d.readStations("../Data/Project1Data/stations.csv");
    bool b = d.readNetworks("../Data/Project1Data/network.csv");
    cout << endl << a << endl;
    cout << b << endl;
    cout << d.getMaxFlow(2,6);
    cout << "\n\n";

    vector<int> sources = d.trainSources();
    for (int i : sources){
        Vertex* v = d.getG().findVertex(i);
        cout << setw(25) << v->getStation()->getName() << "\t" << v->getStation()->getLine() << endl;
    }

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
