//
// Created by Guilherme Monteiro on 03/03/2023.
//

#ifndef DA_PROJECT1_DATA_H
#define DA_PROJECT1_DATA_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "Station.h"
#include "Graph.h"

using namespace std;
class Data {
private:
    Graph g;
    map<string, int> names;

public:
    Graph getG() const;
    map<string, int> getNames() const;

    void setG(Graph g);
    // ~Data();

public:
     bool readStations(string filename);
     bool readNetworks(string filename);

     double getMaxFlow(int source, int target);
     bool path(int source, int target);
     double findBottleneck(int target);
     void augmentPath(int target, double bottleneck);

     pair<vector<pair<Station*,Station*>>,double> stationPairs();
    double nrTrainsArriving(int id);
};


#endif //DA_PROJECT1_DATA_H
