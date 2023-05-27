#ifndef SDIZOPROJEKT2_NLIST_H
#define SDIZOPROJEKT2_NLIST_H
#include <functional>

struct NeighbourNode {
    int neighbour;
    int weight;
    NeighbourNode *previous;
    NeighbourNode *next;
};

class NList {
private:
    int _size = 0;
    NeighbourNode *head = nullptr;
    NeighbourNode *tail = nullptr;
    NeighbourNode* findByIndex(int index);
public:
    ~NList();

    void removeFront();
    void remove(int index);
    void removeEnd();

    void pushFront(int neighbour, int weight);
    void insert(int index, int neighbour, int weight);
    void pushEnd(int neighbour, int weight);

    void print();
    void printFormatted();
    void printBackwards();

    int getSize();
    bool isEmpty();

    int get(int index);
    int getWeight(int index);
    int find(int neighbour);

    void foreach(std::function<void(int)> iterator);
};


#endif //SDIZOPROJEKT2_NLIST_H
