#ifndef SDIZOPROJEKT2_MATRIXGRAPH_H
#define SDIZOPROJEKT2_MATRIXGRAPH_H


#include "iostream"
#include "Graph.h"
#include <iomanip>
#include "LinkedList.h"
#include "KruskalHelper.h"

class MatrixGraph : public Graph {
private:
    int _nodes, _edges;
    int **_innerMatrix;     //dwuwymiarowa tablica
    KruskalHelper *kruskalHelper;
public:

    MatrixGraph(int nodes, int edges);

    virtual ~MatrixGraph();

    void addEdge(int v1, int v2, int weight) override;

    void print() override;

    // route
    void dijkstra(int startingVerticle) override;

    void bellmanFord(int startingVerticle) override;

    // MST
    void kruskal() override;

    void prim(int x) override;

    // max flow
    void fordFulkerson(int startingVerticle) override;

};


#endif //SDIZOPROJEKT2_MATRIXGRAPH_H
