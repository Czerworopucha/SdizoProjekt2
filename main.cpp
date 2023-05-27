#include <iostream>
#include "FileReader.h"
int main() {
    auto graphN = FileReader::loadGraphFromFile("../test.txt", GraphType::NEIGHBOURS_LIST);
    graphN->print();

    auto graphM = FileReader::loadGraphFromFile("../test.txt", GraphType::MATRIX);
    graphM->print();

    graphM->bellmanFord(0);
    graphN->bellmanFord(0);

    return 0;
}
