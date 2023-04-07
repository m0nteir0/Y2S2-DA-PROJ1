#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::addVertex(Vertex* v) {
    if (findVertex(v->getId()) != nullptr)
        return false;
    vertexSet.push_back(v);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}
bool Graph::addEdge(Vertex* v1,Vertex* v2, double w, string service) {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

bool Graph::addBidirectionalEdge(Vertex* v1, Vertex* v2, double w, string service) {

    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service);
    auto e2 = v2->addEdge(v1, w, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}
/**
 * //verificar
 * Desativa as estações fornecidas( e consequentemente os segmentos que têm ligação a essas estações), através do parâmetro 'available' das Edges.
 * COMPLEXIDADE: O(V*E)
 * @param stations vetor de números inteiros que coorespondem aos ids das estações a desativar
*/
void Graph::disableStations(vector<int> stations){
    for (int i : stations){
        Vertex* v = findVertex(i);
        for (auto e : v->getAdj()) e->setAvailable(false);
        for (auto e : v->getIncoming()) e->setAvailable(false);
    }
}

/**
 * //verificar
 * Desativa os segmentos fornecidos, através do seu parâmetro 'available'.
 * COMPLEXIDADE: O(V*E)
 * @param lines vetor de pares de inteiros, que correspondem aos ids das estações que formam o segmento de linha a desativar
 */
void Graph::disableLines(vector<pair<int,int>> lines){
    for (pair<int,int> p : lines){

        Vertex* v = findVertex(p.first);
        for (auto e : v->getAdj()) if (e->getDest()->getId() == p.second) {e->setAvailable(false); break;}
        for (auto e : v->getIncoming()) if (e->getOrig()->getId() == p.second) {e->setAvailable(false); break;}
    }
}
/**
 * Dá reset à todas as linhas do grafo, reativando-as.
 * COMPLEXIDADE: O(V*E)
 */
void Graph::resetLines(){
    for(auto v : vertexSet){
        for(auto e : v->getAdj()){
            e->setAvailable(true);
        }
    }
}
