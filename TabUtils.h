#ifndef SDIZOPROJEKT2_TABUTILS_H
#define SDIZOPROJEKT2_TABUTILS_H

class TabUtils {

public:
    TabUtils();

    virtual ~TabUtils();

    static bool isEmpty(int *tab, int nodes);
    static bool inQueue(int *tab, int v);
    static int lowestValue(int *tab, int nodes);
    static int lowestValueInTab(int *tab1, int *tab2, int nodes);
};


#endif //SDIZOPROJEKT2_TABUTILS_H
