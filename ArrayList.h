#ifndef SDIZOPROJEKT2_ARRAYLIST_H
#define SDIZOPROJEKT2_ARRAYLIST_H

struct Edge{
    int v1, v2, weight;
};

class ArrayList {
public:
    int size;
    Edge *header;

    ArrayList();

    virtual ~ArrayList();

    void addEnd(Edge value);

    void addStart(Edge value);

    void addElementAt(Edge value, int index);

    void removeEnd();

    void removeStart() ;

    void removeElementAt(int index);

    Edge *getElementAt(int index) const;

    Edge *getElementWithValue(int value) const;

    int indexOf(int value) const;

    void displayAllElements();

    void displayAllElementsBackwards() const;

private:
    void copy(const Edge *source, Edge *destination, int amount, int offsetSource = 0, int offsetDestination = 0);
};


#endif //SDIZOPROJEKT2_ARRAYLIST_H
