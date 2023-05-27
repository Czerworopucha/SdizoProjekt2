#ifndef SDIZOPROJEKT2_TABUTILS_H
#define SDIZOPROJEKT2_TABUTILS_H


class TabUtils {

public:
    TabUtils();

    virtual ~TabUtils();

    static bool isEmpty(int *tab);
    static bool inTab(int *tab, int v);
    static int lowestValue(int *tab);
    static int lowestValueInTab(int *tab1, int *tab2);
};

#endif //SDIZOPROJEKT2_TABUTILS_H
