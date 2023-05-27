#ifndef SDIZOPROJEKT2_GRAPH_H
#define SDIZOPROJEKT2_GRAPH_H


enum GraphType {NEIGHBOURS_LIST, MATRIX};

class Graph
{
public:
    void virtual addEdge(int v1, int v2, int weight) = 0;
    void virtual print() = 0;

    // route
    void virtual dijkstra(int startingVerticle) = 0;
    void virtual bellmanFord(int startingVerticle) = 0;

    // MST
    void virtual kruskal() = 0;
    void virtual prim(int startingVerticle) = 0;

    // max flow
    void virtual fordFulkerson(int startingVerticle) = 0;
};



#endif //SDIZOPROJEKT2_GRAPH_H
