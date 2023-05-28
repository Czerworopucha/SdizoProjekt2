#ifndef SDIZOPROJEKT2_MATRIXGRAPH_H
#define SDIZOPROJEKT2_MATRIXGRAPH_H


#include "iostream"
#include "Graph.h"
#include <iomanip>
#include "LinkedList.h"
#include "KruskalHelper.h"

class MatrixGraph : public Graph {
private:
    bool _verbose = true;
    int _nodes, _edges = 0;
    int **_innerMatrix; // dwuwymiarowa tablica
    KruskalHelper *kruskalHelper;
public:
    MatrixGraph(int nodes, bool verbose);
    MatrixGraph(int nodes);
    MatrixGraph(int nodes, bool verbose, int **innerMatrix);
    bool isConnected() override;
    int getNodesCount() override;
    bool edgeExists(int v1, int v2) override;

    virtual ~MatrixGraph();

    void addEdge(int v1, int v2, int weight) override;
    void print() override;

    void dijkstra(int startingVerticle) override;
    void bellmanFord(int startingVerticle) override;

    void kruskal() override;
    void prim(int x) override;
};


#endif //SDIZOPROJEKT2_MATRIXGRAPH_H
