//
// Created by Guilherme Monteiro on 03/03/2023.
//

#ifndef DA_PROJECT1_DATA_H
#define DA_PROJECT1_DATA_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

#include "station.h"
#include "graph.h"

using namespace std;
class Data {
private:
    Graph g;
    set<string> names;
public:
    Graph getG() const;

    void setG(Graph g);

public:
     bool readStations(string filename);
     bool readNetworks(string filename);
};


#endif //DA_PROJECT1_DATA_H
