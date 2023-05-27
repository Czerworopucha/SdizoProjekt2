#include "LinkedList.h"
#include <iostream>

LinkedList::~LinkedList(){
    Node *node = head;

    while(node != nullptr){
        Node *oldNode = node;
        node = node->next;
        delete(oldNode);
    }
}

void LinkedList::pushFront(int value){
    _size += 1;
    Node *newNode = new Node;
    newNode->value = value;
    newNode->previous = nullptr;

    if(head == nullptr){
        newNode->next = nullptr;

        head = newNode;
        tail = newNode;
        return;
    }

    newNode->next = head;
    head->previous = newNode;
    head = newNode;
}

void LinkedList::pushEnd(int value) {
    _size += 1;
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if(tail == nullptr){
        newNode->previous = nullptr;

        head = newNode;
        tail = newNode;
        return;
    }

    newNode->previous = tail;
    tail->next = newNode;
    tail = newNode;
}

void LinkedList::insert(int index, int value){
    if(index == 0){
        pushFront(value);
        return;
    }

    if(index == _size){
        pushEnd(value);
        return;
    }

    _size += 1;

    Node *node = findByIndex(index);

    if(node == nullptr) return;

    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = node;
    newNode->previous = node->previous;

    node->previous->next = newNode;
    node->previous = newNode;
}

int LinkedList::get(int index){
    return findByIndex(index)->value;
}

Node* LinkedList::findByIndex(int index){
    if(index < 0 || index >= _size) return nullptr;

    Node *node;

    if(index <= _size / 2){
        node = head;
        for(int i = 0; i < index; ++i){
            node = node->next;
        }
    } else {
        node = tail;
        for(int i = _size - 1; i >= index; --i){
            node = node->previous;
        }
    }

    return node;
}

void LinkedList::removeFront(){
    if(head == nullptr) return;

    _size -= 1;
    Node *newHead = head->next;
    delete(head);
    head = newHead;

    if(head == nullptr || head->next == nullptr){
        tail = head;
    }

    if(head != nullptr){
        head->previous = nullptr;
    }
}

void LinkedList::remove(int index){
    if(index == 0){
        removeFront();
        return;
    }
    if(index == _size - 1){
        removeEnd();
        return;
    }

    Node *node = findByIndex(index);

    if(node == nullptr) return;

    _size -= 1;

    Node *prev = node->previous;

    prev->next = node->next;
    prev->next->previous = node->previous;

    delete(node);
}

void LinkedList::removeEnd(){
    if(tail == nullptr) return;

    _size -= 1;
    Node *newTail = tail->previous;
    delete(tail);
    tail = newTail;

    if(tail == nullptr || tail->previous == nullptr){
        head = tail;
    }

    if(tail != nullptr){
        tail->next = nullptr;
    }
}

void LinkedList::print() {
    Node *node = head;
    std::cout << "[ ";
    while(node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << "]" << std::endl;
}

void LinkedList::printFormatted() {
    Node *node = head;
    std::cout << "[" << std::endl;
    while(node != nullptr){
        std::cout << "|" <<node->previous << " " << node << ":" << node->value << " " << node->next << "|" << std::endl;
        node = node->next;
    }
    std::cout << "]" << std::endl;
}

void LinkedList::printBackwards() {
    Node *node = tail;
    std::cout << "[ ";
    while(node != nullptr){
        std::cout << node->value << " ";
        node = node->previous;
    }
    std::cout << "]" << std::endl;
}

int LinkedList::find(int value){
    int i = 0;
    Node *node = head;
    while (node != nullptr){
        if(node -> value == value)
            return i;
        node = node->next;
        ++i;
    }

    return -1;
}

int LinkedList::getSize(){
    return _size;
}

bool LinkedList::isEmpty() {
    return _size <= 0;
}

void LinkedList::foreach(std::function<void(int)> iterator) {
    auto node = head;

    while(node != nullptr) {
        iterator(node->value);
        node = node->next;
    }
}

bool LinkedList::contains(int value) {
    return find(value) != -1;
}