#ifndef SDIZOPROJEKT2_GRAPH_H
#define SDIZOPROJEKT2_GRAPH_H


enum GraphType {NEIGHBOURS_LIST, MATRIX};
static const char *graphTypeString[] = {"NEIGHBOURS_LIST", "MATRIX"};

class Graph
{
public:
    int virtual getNodesCount() = 0;
    void virtual addEdge(int v1, int v2, int weight) = 0;
    void virtual print() = 0;
    bool virtual isConnected() = 0;
    bool virtual edgeExists(int v1, int v2) = 0;

    void virtual dijkstra(int startingVerticle) = 0;
    void virtual bellmanFord(int startingVerticle) = 0;

    void virtual kruskal() = 0;
    void virtual prim(int startingVerticle) = 0;
};



#endif //SDIZOPROJEKT2_GRAPH_H
