#ifndef SDIZOPROJEKT2_HEAP_H
#define SDIZOPROJEKT2_HEAP_H
#include "ArrayList.h"

class Heap {
public:
    Heap();

    void add(Edge value);

    Edge removeTop();

    void displayAsList();

    void displayAsTree();

    Edge *getElementByValue(int value);

    virtual ~Heap();


    ArrayList *array;
    int size;

    int getParentIndex(int index);

    int getLeftChildIndex(int index);

    int getRightChildIndex(int index);

    void swap(Edge *source, Edge *destination);

    Edge *getLeftChild(int index);

    Edge *getRightChild(int index);

    int min(int left, int right);

    void displaySubTree(int level, int index);


};


#endif //SDIZOPROJEKT2_HEAP_H
