#include "ArrayList.h"
#include <iostream>

ArrayList::ArrayList() {
    this->header = new Edge[0];
    this->size = 0;
}

ArrayList::~ArrayList() {
    delete[] this->header;
}

void ArrayList::addEnd(Edge value) {
    auto newArray = new Edge[size + 1];
    copy(header, newArray, size);
    newArray[size] = value;
    size++;
    delete header;
    header = newArray;
}

void ArrayList::addStart(Edge value) {
    auto newArray = new Edge[size + 1];
    copy(header, newArray, size, 0, 1);
    newArray[0] = Edge();
    size++;
    delete header;
    header = newArray;
}

void ArrayList::addElementAt(Edge value, int index) {
    if (index > size || index < 0)
        return;

    if (index == size) {
        addEnd(value);
        return;
    }

    auto newArray = new Edge[size + 1];
    copy(header, newArray, index);
    newArray[index] = value;
    copy(header, newArray, size + 1 - index, index, index + 1);
    size++;
    delete header;
    header = newArray;
}

void ArrayList::removeEnd() {
    if (size == 0) return;

    auto newArray = new Edge[size - 1];
    copy(header, newArray, size - 1);
    size--;
    delete header;
    header = newArray;
}

void ArrayList::removeStart() {
    if (size == 0) return;

    auto newArray = new Edge[size - 1];
    copy(header, newArray, size, 1, 0);
    size--;
    delete header;
    header = newArray;
}

void ArrayList::removeElementAt(int index) {
    if (index >= size || index < 0)
        return;
    auto newArray = new Edge[size - 1];
    copy(header, newArray, index);
    copy(header, newArray, size - index, index + 1, index);
    size--;
    delete header;
    header = newArray;

}

void ArrayList::copy(const Edge *source, Edge *destination, int amount, int offsetSource, int offsetDestination) {
    for (int i = 0; i < amount; ++i) {
        destination[i + offsetDestination] = source[i + offsetSource];
    }
}

Edge *ArrayList::getElementAt(int index) const {
    if (index >= size || index < 0)
        return nullptr;
    return &header[index];
}

Edge *ArrayList::getElementWithValue(int value) const {
    for (int i = 0; i < size; ++i) {
        if (header[i].weight == value) return &header[i];
    }
    return nullptr;
}

int ArrayList::indexOf(int value) const {
    for (int i = 0; i < size; ++i) {
        if (header[i].weight == value) return i;
    }
    return -1;
}

void ArrayList::displayAllElements() {
    for (int i = 0; i < size; ++i) {
        std::cout << i << " -> " << header[i].weight << "\n";
    }
}

void ArrayList::displayAllElementsBackwards() const {
    for (int i = size - 1; i >= 0; i--) {
        std::cout << i << " -> " << header[i].weight << "\n";
    }
}
