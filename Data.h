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
    double sumFlow;
    double sumFlowSub;
};

using namespace std;
class Data {
private:
    string stations;
    string network;

    Graph g;
    map<string, int> names;

    unordered_set<string> districts;
    unordered_set<string> municipalities;

    queue<int> trainSources;

public:
    const string &getStations() const;
    const string &getNetwork() const;

    Graph getG() const;
    map<string, int> getNames() const;

    void setG(Graph g);
    // ~Data();

     bool readStations(string filename);
     bool readNetwork(string filename);
     void findTrainSources();

     //T2.1
     double getMaxFlow(queue<int> source, int target);
     bool path(queue<int> source, int target);
     double findBottleneck(int target);
     void augmentPath(int target, double bottleneck);

     //T2.2
     pair<vector<pair<Station*,Station*>>,double> stationPairs();
     //T2.3
     vector<pair<string, double>> topMunicipalities();
     vector<pair<string, double>> topDistricts();
     //T2.4
     double nrTrainsArriving(int target);

     //T3.1
     pair<double,double> maxTrainsCost(int source, int target);
     void cheapestPath(int source, int target);

     //T4.1
    double getMaxFlowSub(queue<int> source, int target);
    bool pathSub(queue<int> source, int target);

    //T4.2
    vector<Result> topAffected(int k);

};


#endif //DA_PROJECT1_DATA_H
