#ifndef SDIZOPROJEKT2_KRUSKALHELPER_H
#define SDIZOPROJEKT2_KRUSKALHELPER_H


#include "Heap.h"

class KruskalHelper {
private:
    int *group;
    int nodes;
    void makeSet();
    void mergeGroups(int v1, int v2);

public:
    KruskalHelper(int nodes);
    ~KruskalHelper();
    void findMST(Heap *edges, bool verbose);
};


#endif //SDIZOPROJEKT2_KRUSKALHELPER_H
