#ifndef DA_PROJECT1_VERTEXEDGE_H
#define DA_PROJECT1_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "Station.h"
#include "MutablePriorityQueue.h"

class Edge;


/************************* Vertex  **************************/

class Vertex {
public:
    friend class MutablePriorityQueue<Vertex>;

    Vertex(int id);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    Station* getStation() const;

    void setId(int info);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);

    void setStation(Station* station);

    Edge * addEdge(Vertex *dest, double w);
    Edge * addEdge(Vertex *dest, double w, string service);
    bool removeEdge(int destID);

    bool operator<(const Vertex &rhs) const;
protected:
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges
    Station* station; // station

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    std::vector<Edge *> incoming; // incoming edges
    Edge *path = nullptr;

    int queueIndex = 0;
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);
    Edge(Vertex *orig, Vertex *dest, double w, string service);

    Vertex * getDest() const;
    double getWeight() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    string getService() const;
    bool isAvailable() const;

    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setService(string service);
    void setAvailable(bool available);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    string service;

    // auxiliary fields
    bool available = true;
    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;
    double flow; // for flow-related problems
};

#endif //DA_PROJECT1_VERTEXEDGE_H
