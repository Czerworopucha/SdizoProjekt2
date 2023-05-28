#ifndef SDIZOPROJEKT2_NLISTGRAPH_H
#define SDIZOPROJEKT2_NLISTGRAPH_H
#include "Graph.h"
#include "NList.h"
#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "KruskalHelper.h"

class NListGraph : public Graph{
private:
    bool _verbose = true;
    int _nodes, _edges;
    NList **_neighbours;
    KruskalHelper *kruskalHelper;
public:
    NListGraph(int nodes, bool verbose);
    NListGraph(int nodes);
    int getNodesCount() override;
    bool isConnected() override;
    bool edgeExists(int v1, int v2) override;

    virtual ~NListGraph();

    void addEdge(int v1, int v2, int weight) override;
    void print() override;

    // route
    void dijkstra(int startingVerticle) override;
    void bellmanFord(int startingVerticle) override;

    // MST
    void kruskal() override;
    void prim(int startingVerticle) override;
};


#endif //SDIZOPROJEKT2_NLISTGRAPH_H
