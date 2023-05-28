#include "KruskalHelper.h"
#include <iostream>

KruskalHelper::KruskalHelper(int nodes) {
    this->nodes = nodes;
    this->group = new int[nodes];
}

KruskalHelper::~KruskalHelper() {
    delete[] group;
}

void KruskalHelper::findMST(Heap *edges, bool verbose) {
    auto result = new ArrayList();
    int weightSum = 0;
    makeSet();

    while (edges->size != 0) {
        auto edge = edges->removeTop();

        if (group[edge.v1] != group[edge.v2]) {
            result->addEnd(edge);
            mergeGroups(edge.v1, edge.v2);
            weightSum += edge.weight;
        }
    }

    if(!verbose) return;
    std::cout << "\n\n Sum of weights: " << weightSum << "\n";
    for (int i = 0; i < result->size; i++) {
        std::cout << " " << result->getElementAt(i)->v1 << " -> " << result->getElementAt(i)->v2 << " : "
                  << result->getElementAt(i)->weight << " \n";
    }
}

void KruskalHelper::makeSet() {
    for (int i = 0; i < nodes; i++) {
        group[i] = i;
    }
}

void KruskalHelper::mergeGroups(int v1, int v2) {
    int groupToReplace = group[v1];

    for (int i = 0; i < nodes; i++) {
        if (group[i] == groupToReplace) {
            group[i] = group[v2];
        }
    }
}
