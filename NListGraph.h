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
    int _nodes, _edges;
    NList **_neighbours;
    KruskalHelper *kruskalHelper;
public:

    NListGraph(int nodes, int edges);
    virtual ~NListGraph();

    void addEdge(int v1, int v2, int weight) override;
    void print() override;

    // route
    void dijkstra(int startingVerticle) override;
    void bellmanFord(int startingVerticle) override;

    // MST
    void kruskal() override;
    void prim(int startingVerticle) override;

    // max flow
    void fordFulkerson(int startingVerticle) override;
};


#endif //SDIZOPROJEKT2_NLISTGRAPH_H
