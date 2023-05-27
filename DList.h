#ifndef SDIZOPROJEKT2_DLIST_H
#define SDIZOPROJEKT2_DLIST_H
#include <string>
#include <functional>

class DList {
private:
    struct dlistNode {
        dlistNode *next, *prev;
        int data;

        dlistNode()= default;
        dlistNode(dlistNode *next, dlistNode *prev, int data){
            this->next = next;
            this->prev = prev;
            this->data = data;
        }
    };
    struct dlistVar {
        dlistNode *head, *tail;
        unsigned count;

        dlistVar()= default;
        dlistVar(dlistNode *head, dlistNode *tail, unsigned count){
            this->head = head;
            this->tail = tail;
            this->count = count;
        }
    };
    dlistVar *list;

public:

    DList();

    virtual ~DList();

    void addFirst(int data);

    void addLast(int data);

    void addAny(int data, int index);

    void deleteFirst();

    void deleteLast();

    void deleteAny(int index);

    void printDListForward();

    void printDListBackward();

    bool searchDList(int data);

    void readData(const std::string &FileName);

    unsigned int count();

    void foreach(std::function<void(int)> iterator);

    unsigned int findIndex(int data);

};


#endif //SDIZOPROJEKT2_DLIST_H
