#ifndef DA_PROJECT1_GRAPH_H
#define DA_PROJECT1_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "VertexEdge.h"

class Graph {
public:
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id);
    bool addVertex(Vertex* v);
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    bool addEdge(Vertex* v1,Vertex* v2, double w, string service);

    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(Vertex* v1, Vertex* v2, double w, string service);

    void disableStations(vector<int> stations);
    void disableLines(vector<pair<int,int>> lines);
    void resetLines();

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

};

#endif //DA_PROJECT1_GRAPH_H
