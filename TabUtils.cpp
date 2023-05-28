#include "TabUtils.h"
#include <iostream>



bool TabUtils::isEmpty(int *tab, int nodes){
    for(int i=0; i < nodes; i++)
        if (tab[i] != INT_MAX) return false;
    return true;
}

int TabUtils::lowestValue(int *tab, int nodes){
    int lowest = tab[0];
    for(int i = 0; i < nodes; i++)
        if (tab[i] < tab[lowest]) lowest = i;
    return lowest;
}

int TabUtils::lowestValueInTab(int *tab1, int *tab2, int nodes){
    if(!isEmpty(tab2, nodes)) {
        int lowest = INT_MAX;
        int indexLowest = 0;
        for (int i = 0; i < nodes; i++)
            if (inQueue(tab2, i))
                if (tab1[i] < lowest) {
                    lowest = tab1[i];
                    indexLowest = i;
                }
        return indexLowest;
    }
    return INT_MAX;
}


bool TabUtils::inQueue(int *tab, int v){
    if (tab[v] != INT_MAX) return true;
    return false;
}

TabUtils::TabUtils() {}

TabUtils::~TabUtils() {

}