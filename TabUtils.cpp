#include "TabUtils.h"
#include <iostream>



bool TabUtils::isEmpty(int *tab){
    for(int i=0; i < sizeof(tab); i++)
        if (tab[i] != INT_MAX) return false;
    return true;
}
int TabUtils::lowestValue(int *tab){
    int lowest = tab[0];
    for(int i = 0; i < sizeof(tab); i++)
        if (tab[i] < tab[lowest]) lowest = i;
    return lowest;
}

int TabUtils::lowestValueInTab(int *tab1, int *tab2){
    if(!isEmpty(tab2)) {
        int lowest = INT_MAX;
        int indexLowest = 0;
        for (int i = 0; i < sizeof(tab1); i++)
            if (inTab(tab2, i))
                if (tab1[i] < lowest) {
                    lowest = tab1[i];
                    indexLowest = i;
                }
        return indexLowest;
    }
    return INT_MAX;
}


bool TabUtils::inTab(int *tab, int v){
    for(int i=0; i < sizeof(tab); i++)
        if (tab[i] == v) return true;
    return false;
}

TabUtils::TabUtils() {}

TabUtils::~TabUtils() {

}
