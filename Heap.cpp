#include "Heap.h"
#include <cmath>
#include <iostream>


Heap::Heap() {
    this->array = new ArrayList();
    this->size = 0;
}

Heap::~Heap() {
    delete this->array;
}

void Heap::add(Edge value) {
    array->addEnd(value);
    auto index = size;
    size++;

    auto parentIndex = getParentIndex(index);
    auto currentElement = array->getElementAt(index);
    auto parentElement = array->getElementAt(parentIndex);

    while (parentElement && currentElement->weight <= parentElement->weight) {
        swap(parentElement, currentElement);
        index = parentIndex;
        parentIndex = getParentIndex(index);
        currentElement = array->getElementAt(index);
        parentElement = array->getElementAt(parentIndex);
    }
}

void Heap::displayAsList() {
    this->array->displayAllElements();
}

int Heap::getParentIndex(int index) {
    if (index == 0) return -1;

    return floor((index - 1) / 2);
}

int Heap::getLeftChildIndex(int index) {
    return 2 * index + 1;
}

int Heap::getRightChildIndex(int index) {
    return 2 * index + 2;
}

void Heap::swap(Edge *source, Edge *destination) {
    auto temp = *source;
    *source = *destination;
    *destination = temp;
}

Edge Heap::removeTop() {
    if (size == 0) return Edge();

    auto root = array->getElementAt(0);

    auto toReturn = *root;


    auto lastLeaf = array->getElementAt(size - 1);
    swap(root, lastLeaf);
    array->removeEnd();
    size--;
    auto currentIndex = 0;

    auto currentElement = array->getElementAt(currentIndex);
    auto left = getLeftChildIndex(currentIndex);
    auto right = getRightChildIndex(currentIndex);
    auto maxChildIndex = min(left, right);
    auto maxChild = array->getElementAt(maxChildIndex);

    while (maxChild && maxChild->weight <= currentElement->weight) {

        swap(maxChild, currentElement);
        currentIndex = maxChildIndex;

        currentElement = array->getElementAt(currentIndex);
        left = getLeftChildIndex(currentIndex);
        right = getRightChildIndex(currentIndex);

        maxChildIndex = min(left, right);
        maxChild = array->getElementAt(maxChildIndex);
    }

    return toReturn;
}

Edge *Heap::getLeftChild(int index) {
    return array->getElementAt(getLeftChildIndex(index));
}

Edge *Heap::getRightChild(int index) {
    return array->getElementAt(getRightChildIndex(index));
}

int Heap::min(int leftIndex, int rightIndex) {

    auto left = array->getElementAt(leftIndex);
    auto right = array->getElementAt(rightIndex);

    if (!left && !right) return -1;

    if (!left) return rightIndex;
    if (!right) return leftIndex;

    return right->weight <= left->weight ? rightIndex : leftIndex;
}

void Heap::displayAsTree() {
    displaySubTree(0, 0);
}

void Heap::displaySubTree(int level, int index) {
    if (index >= size) return;

    for (int i = 0; i < level; ++i) {
        if (i == level - 1) {
            std::cout << "+---";
        } else
            std::cout << "    ";
    }
    std::cout << array->getElementAt(index)->weight << "\n";
    displaySubTree(level + 1, getLeftChildIndex(index));
    displaySubTree(level + 1, getRightChildIndex(index));
}

Edge *Heap::getElementByValue(int value) {
    for (int i = 0; i < size; ++i) {
        auto current = array->getElementAt(i);
        if (current->weight == value) {
            return current;
        }
    }
    return nullptr;
}

