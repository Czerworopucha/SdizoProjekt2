#ifndef SDIZOPROJEKT2_FILEREADER_H
#define SDIZOPROJEKT2_FILEREADER_H


#include "fstream"
#include "iostream"
#include "MatrixGraph.h"

class FileReader {
public:
    FileReader();

    virtual ~FileReader();

    static Graph *loadGraphFromFile(const std::string &filename, GraphType type);

};


#endif //SDIZOPROJEKT2_FILEREADER_H
