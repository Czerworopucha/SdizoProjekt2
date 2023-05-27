#include "NList.h"
#include <iostream>

NList::~NList() {
    NeighbourNode *node = head;

    while (node != nullptr) {
        NeighbourNode *oldNode = node;
        node = node->next;
        delete (oldNode);
    }
}

void NList::pushFront(int neighbour, int weight) {
    _size += 1;
    NeighbourNode *newNode = new NeighbourNode;
    newNode->neighbour = neighbour;
    newNode->weight = weight;
    newNode->previous = nullptr;

    if (head == nullptr) {
        newNode->next = nullptr;

        head = newNode;
        tail = newNode;
        return;
    }

    newNode->next = head;
    head->previous = newNode;
    head = newNode;
}

void NList::pushEnd(int neighbour, int weight) {
    _size += 1;
    NeighbourNode *newNode = new NeighbourNode;
    newNode->neighbour = neighbour;
    newNode->weight = weight;
    newNode->next = nullptr;

    if (tail == nullptr) {
        newNode->previous = nullptr;

        head = newNode;
        tail = newNode;
        return;
    }

    newNode->previous = tail;
    tail->next = newNode;
    tail = newNode;
}

void NList::insert(int index, int neighbour, int weight) {
    if (index == 0) {
        pushFront(neighbour, weight);
        return;
    }

    if (index == _size) {
        pushEnd(neighbour, weight);
        return;
    }

    _size += 1;

    NeighbourNode *node = findByIndex(index);

    if (node == nullptr) return;

    NeighbourNode *newNode = new NeighbourNode;
    newNode->neighbour = neighbour;
    newNode->weight = weight;
    newNode->next = node;
    newNode->previous = node->previous;

    node->previous->next = newNode;
    node->previous = newNode;
}

int NList::get(int index) {
    return findByIndex(index)->neighbour;
}

int NList::getWeight(int index) {
    return findByIndex(index)->weight;
}

NeighbourNode *NList::findByIndex(int index) {
    if (index < 0 || index >= _size) return nullptr;

    NeighbourNode *node;

    if (index <= _size / 2) {
        node = head;
        for (int i = 0; i < index; ++i) {
            node = node->next;
        }
    } else {
        node = tail;
        for (int i = _size - 1; i > index; --i) {
            node = node->previous;
        }
    }

    return node;
}

void NList::removeFront() {
    if (head == nullptr) return;

    _size -= 1;
    NeighbourNode *newHead = head->next;
    delete (head);
    head = newHead;

    if (head == nullptr || head->next == nullptr) {
        tail = head;
    }

    if (head != nullptr) {
        head->previous = nullptr;
    }
}

void NList::remove(int index) {
    if (index == 0) {
        removeFront();
        return;
    }
    if (index == _size - 1) {
        removeEnd();
        return;
    }

    NeighbourNode *node = findByIndex(index);

    if (node == nullptr) return;

    _size -= 1;

    NeighbourNode *prev = node->previous;

    prev->next = node->next;
    prev->next->previous = node->previous;

    delete (node);
}

void NList::removeEnd() {
    if (tail == nullptr) return;

    _size -= 1;
    NeighbourNode *newTail = tail->previous;
    delete (tail);
    tail = newTail;

    if (tail == nullptr || tail->previous == nullptr) {
        head = tail;
    }

    if (tail != nullptr) {
        tail->next = nullptr;
    }
}

void NList::print() {
    NeighbourNode *node = head;
    std::cout << "[ ";
    while (node != nullptr) {
        std::cout << " {N: " << node->neighbour << " W: " << node->weight << "} ";
        node = node->next;
    }
    std::cout << "]";
}

void NList::printFormatted() {
    NeighbourNode *node = head;
    std::cout << "[" << std::endl;
    while (node != nullptr) {
        std::cout << "|" << node->previous << " " << node << ":" << node->neighbour << " " << node->next << "|"
                  << std::endl;
        node = node->next;
    }
    std::cout << "]" << std::endl;
}

void NList::printBackwards() {
    NeighbourNode *node = tail;
    std::cout << "[ ";
    while (node != nullptr) {
        std::cout << node->neighbour << " ";
        node = node->previous;
    }
    std::cout << "]" << std::endl;
}

int NList::find(int neighbour) {
    int i = 0;
    NeighbourNode *node = head;
    while (node != nullptr) {
        if (node->neighbour == neighbour)
            return i;
        node = node->next;
        ++i;
    }

    return -1;
}

int NList::getSize() {
    return _size;
}

bool NList::isEmpty() {
    return _size <= 0;
}

void NList::foreach(std::function<void(int)> iterator) {
    auto node = head;

    while (node != nullptr) {
        iterator(node->neighbour);
        node = node->next;
    }
}