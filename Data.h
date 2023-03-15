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
#include <unordered_set>

#include "Station.h"
#include "Graph.h"

struct Result {
    Station * s;
    double dif;
    int sumFlow;
    int sumFlowSub;
};

using namespace std;
class Data {
private:
    Graph g;
    map<string, int> names;
    unordered_set<string> districts;
    unordered_set<string> municipalities;

public:
    Graph getG() const;
    map<string, int> getNames() const;

    void setG(Graph g);
    // ~Data();

public:
     bool readStations(string filename);
     bool readNetworks(string filename);

     //T2.1
     double getMaxFlow(int source, int target);
     bool path(int source, int target);
     double findBottleneck(int target);
     void augmentPath(int target, double bottleneck);

     //T2.2
     pair<vector<pair<Station*,Station*>>,double> stationPairs();
     //T2.3
     vector<pair<string, double>> topDistricts();
     //T2.4
     double nrTrainsArriving(int id);
     vector<int> trainSources();

     //T3.1
     void cheapestPath(int source, int target);

     //T4.1
    double getMaxFlowSub(int source, int target);
    bool pathSub(int source, int target);

    //T4.2
    vector<Result> topAffected(int k);

};


#endif //DA_PROJECT1_DATA_H
