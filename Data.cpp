//
// Created by Guilherme Monteiro on 03/03/2023.
//

#include "Data.h"

bool Data::readStations(string filename) {
    ifstream input(filename);
    string labels = "Name,District,Municipality,Township,Line";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            int id = 1;
            string name, district, municipality, township, line;
            string field;
            vector<string> fields;
            char quote_char = '"';
            while (getline(input, l)) {
                stringstream iss(l);
                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }
                //========================================================
                /*
                cout << "Id: " << id << endl;
                for (int i = 0; i< 5; i++){
                    cout << " " << fields[i] << " |";
                }
                cout << endl;
                */

                name = fields[0];
                district = fields[1];
                municipality = fields[2];
                township = fields[3];
                line = fields[4];

                if(names.insert({name,id}).second){      //(names.insert(name).second) return false if element already exists
                    Station* station = new Station(name,district,municipality,township,line);
                    Vertex* v = new Vertex(id);
                    v->setStation(station);
                    g.addVertex(v);
                    id++;
                }
                fields.clear();
            }
            return true;
        } else cout << "\nFile content is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open the selected file\n";
    return false;
}

bool Data::readNetworks(std::string filename) {
    ifstream input(filename);
    string labels = "Station_A,Station_B,Capacity,Service";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            string station_A, station_B, capacity, service;
            int counter = 1;
            string field;
            vector<string> fields;
            char quote_char = '"';

            while (getline(input, l)) {
                stringstream iss(l);
                Vertex* vA = nullptr; Vertex* vB = nullptr;

                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }
                station_A = fields[0];
                station_B = fields[1];
                capacity = fields[2];
                service = fields[3];
                counter++;
                for (auto v : g.getVertexSet()){ // find vertex
                    Station* s = v->getStation();
                    if(s->getName() == station_A) vA = v;
                    else if(s->getName() == station_B) vB = v;
                    if(vA != nullptr && vB != nullptr) break; // both vertex were found.
                }
                fields.clear();

                if(!g.addBidirectionalEdge(vA, vB, stod(capacity), service)){
                    cout << "\nOn line " << (counter) <<", there are stations that do not exist.\n";
                    //return false;
                }
            }
            return true;
        } else cout << "\nFile content is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open the selected file\n";
    return false;
}

Graph Data::getG() const {
    return g;
}

void Data::setG(Graph g) {
    this->g = g;
}

map<string, int> Data::getNames() const {
    return names;
}

double Data::getMaxFlow(int source, int target) {
    for (Vertex* v : g.getVertexSet()){
        for (Edge* e : v->getIncoming()) {
            e->setFlow(0);

            Edge* reverse = new Edge(e->getDest(), e->getOrig(), e->getWeight());
            reverse->setFlow(0);
            reverse->setReverse(e);
            e->setReverse(reverse);
        }
    }

    double bottleneck;
    while (path(source, target)){
        bottleneck = findBottleneck(target);
        augmentPath(target, bottleneck);
    }

    double maxFlow = 0;
    Vertex* sink = g.findVertex(target);
    for (Edge* e : sink->getIncoming())
        maxFlow += e->getFlow();
    return maxFlow;
}

bool Data::path(int source, int target) {
    for (Vertex* v : g.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<int> s({source});
    g.findVertex(source)->setVisited(true);
    while (!s.empty()){
        Vertex* v = g.findVertex(s.front());
        for (Edge* e : v->getAdj()) {
            if (!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0) {
                s.push(e->getDest()->getId());
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if (e->getDest()->getId() == target)
                    return true;
            }
        }

        for (Edge* e : v->getIncoming()){
            if (e->getReverse()->getOrig() == v && !e->getReverse()->getDest()->isVisited() && e->getReverse()->getFlow() != 0){
                s.push(e->getReverse()->getDest()->getId());
                e->getReverse()->getDest()->setVisited(true);
                e->getReverse()->getDest()->setPath(e->getReverse());
                if (e->getReverse()->getDest()->getId() == target)
                    return true;
            }
        }

        s.pop();
    }
    return false;
}

double Data::findBottleneck(int target) {
    Vertex* v = g.findVertex(target);
    double bottleneck = std::numeric_limits<double>::max();
    while (v->getPath() != nullptr){
        double remaining = v->getPath()->getWeight() - v->getPath()->getFlow();
        if (remaining < bottleneck)
            bottleneck = remaining;
        v = v->getPath()->getOrig();
    }
    return bottleneck;
}

void Data::augmentPath(int target, double bottleneck) {
    Vertex* v = g.findVertex(target);
    while (v->getPath() != nullptr){
        v->getPath()->setFlow(v->getPath()->getFlow() + bottleneck);

        v->getPath()->getReverse()->setFlow(v->getPath()->getReverse()->getFlow() - bottleneck);

        v = v->getPath()->getOrig();
    }
}
