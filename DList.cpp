#include "DList.h"
#include <iostream>
#include <fstream>

using namespace std;

DList::DList() {
    DList::list = list;
    list = new dlistVar(nullptr, nullptr, 0);
}

DList::~DList() {
    delete list;
}

void DList::addFirst(int data){
    if (list->head) {
        dlistNode *newNode = new dlistNode(list->head, nullptr, data);
        list->head = newNode;
        newNode->next->prev = newNode;
        list->count++;
    } else {
        dlistNode *newNode = new dlistNode(nullptr, nullptr, data);
        list->head = newNode;
        list->tail = newNode;
        list->count++;
    }
}

void DList::addLast(int data){
    if (list->head) {
        dlistNode *newNode = new dlistNode(nullptr, list->tail, data);
        list->tail = newNode;
        newNode->prev->next = newNode;
        list->count++;
    } else {
        dlistNode *newNode = new dlistNode(nullptr, nullptr, data);
        list->head = newNode;
        list->tail = newNode;
        list->count++;
    }
}

void DList::addAny(int data, int index) {
    if(index == 0) addFirst(data);
    if(index == list->count) addLast(data);
    if (index > 0 && index < list->count) {
        dlistNode *pointer = new dlistNode;
        pointer = list->head;
        for(int i=0; i < index; i++)
            pointer = pointer->next;
        dlistNode *newNode = new dlistNode(pointer, pointer->prev, data);
        pointer->prev->next = newNode;
        pointer->prev = newNode;
        list->count++;
    }else
        cout << "Invaid index." << endl;
}

void DList::deleteFirst(){
    if (list->head) {
        list->head = list->head->next;
        if(list->head) list->head->prev = nullptr;
        list->count--;
    } else {
        cout << "List is empty." << endl;
    }
}

void DList::deleteLast(){
    if (list->tail) {
        list->tail = list->tail->prev;
        if(list->tail) list->tail->next = nullptr;
        list->count--;
    } else {
        cout << "List is empty." << endl;
    }
}

void DList::deleteAny(int index) {
    if(index == 0) deleteFirst();
    if(index == list->count) deleteLast();
    if (index > 0 && index < list->count) {
        dlistNode *pointer = new dlistNode;
        pointer = list->head;
        for(int i=0; i < index; i++)
            pointer = pointer->next;
        pointer->prev->next = pointer->next;
        pointer->next->prev = pointer->prev;
        list->count++;
    }else
        cout << "Invaid index." << endl;
}

bool DList::searchDList(int data){
    dlistNode *pointer = new dlistNode;
    pointer = list->head;
    int index = 0;
    while(pointer){
        if(pointer->data == data) {
            cout << "Value found at index: " << index << endl;
            return true;
        }
        pointer = pointer->next;
        index++;
    }
    cout << "Didn't found matching value." << endl;
    return false;
}

void DList::printDListForward(){
    cout << "Contents of list" << endl;
    dlistNode *pointer = new dlistNode;
    pointer = list->head;
    while(pointer){
        cout << " <" << pointer->data << "> " << endl;
        pointer = pointer->next;
    }
}

void DList::printDListBackward(){
    cout << "Contents of list" << endl;
    dlistNode *pointer = new dlistNode;
    pointer = list->tail;
    while(pointer){
        cout << " <" << pointer->data << "> " << endl;
        pointer = pointer->prev;
    }
}

void DList::readData(const string &FileName){
    ifstream file;
    file.open(FileName, ios::in);
    int size;
    int val;

    if (file.is_open()) {
        file >> size;
        if (file.fail()) {
            cout << "File error - READ SIZE" << endl;
        } else {
            // tab = new int[size];
            for (int i = 0; i < size; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    break;
                } else {
                    addLast(val);
                }
            }
            file.close();
        }
    } else {
        cout << "File error - OPEN" << endl;
    }
}

unsigned int DList::count() {
    return list->count;
}

void DList::foreach(std::function<void(int)> iterator) {
    auto node = list->head;

    while(node != nullptr) {
        iterator(node->data);
        node = node->next;
    }
}

unsigned int DList::findIndex(int data) {
    auto node = list->head;
    auto i = 0;

    while(node != nullptr) {
        if(node->data != data){
            node = node->next;
            ++i;
            continue;
        }
        return i;
    }

    return -1;
}