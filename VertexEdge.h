//
// Created by Guilherme Monteiro on 03/03/2023.
//

#ifndef DA_PROJECT1_VERTEXEDGE_H
#define DA_PROJECT1_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "Station.h"

class Edge;


/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    //int getNum() const;
    //int getLow() const;
    std::vector<Edge *> getIncoming() const;

    Station* getStation() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    void setNum(int num);
    void setLow(int low);

    void setStation(Station* station);

    Edge * addEdge(Vertex *dest, double w);
    Edge * addEdge(Vertex *dest, double w, string service);
    bool removeEdge(int destID);

    // friend class MutablePriorityQueue<Vertex>;
protected:
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges
    Station* station; // station

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    std::vector<Edge *> incoming; // incoming edges
    Edge *path = nullptr;

    //NAO USAMOS ??
    //bool processing = false; // used by isDAG (in addition to the visited attribute)
    //unsigned int indegree; // used by topsort
    //int num = -1;
    //int low = -1;
    // int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);
    Edge(Vertex *orig, Vertex *dest, double w, string service);


    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    string getService() const;
    bool isAvailable() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setService(string service);
    void setAvailable(bool available);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    string service;
    // auxiliary fields
    bool selected = false;

    bool available = true;
    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};


#endif //DA_PROJECT1_VERTEXEDGE_H
