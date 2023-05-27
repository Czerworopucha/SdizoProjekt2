#ifndef SDIZOPROJEKT2_LINKEDLIST_H
#define SDIZOPROJEKT2_LINKEDLIST_H
#include <functional>

struct Node {
    int value;
    Node *previous;
    Node *next;
};

class LinkedList {
private:
    int _size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
    Node* findByIndex(int index);
public:
    ~LinkedList();

    void removeFront();
    void remove(int index);
    void removeEnd();

    void pushFront(int value);
    void insert(int index, int value);
    void pushEnd(int value);

    void print();
    void printFormatted();
    void printBackwards();

    int getSize();
    bool isEmpty();

    int get(int index);
    int find(int value);

    void foreach(std::function<void(int)> iterator);
    bool contains(int value);
};


#endif //SDIZOPROJEKT2_LINKEDLIST_H
