#ifndef SDIZOPROJEKT2_GENERATOR_H
#define SDIZOPROJEKT2_GENERATOR_H
#include "Graph.h"
#include "MatrixGraph.h"

class Generator {
private:
    static void spTree(int **matrix, int nodes, int *visited);
public:
    static Graph* generate(int nodes, double density, GraphType type, bool verbose = true);
    static MatrixGraph* createMatrix(int nodes, double edgesPercent, int maxEdges, bool verbose = true);
};


#endif //SDIZOPROJEKT2_GENERATOR_H
