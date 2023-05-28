#ifndef SDIZOPROJEKT2_TESTS_H
#define SDIZOPROJEKT2_TESTS_H

#include "Graph.h"
#include <algorithm>

class Tests {
private:
    double primTests(Graph *graph, int retries);
    double kruskalTests(Graph *graph, int retries);
    double dijkstraTests(Graph *graph, int retries);
    double bellmanFordTests(Graph *graph, int retries);
    void gpTest(GraphType type, int nodes, int retries);
public:
    void listTests();
    void matrixTests();
};


#endif //SDIZOPROJEKT2_TESTS_H
