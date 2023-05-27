#include "FileReader.h"
#include "NListGraph.h"

Graph *FileReader::loadGraphFromFile(const std::string &filename, GraphType type) {
    Graph *graph = nullptr;
    int edgeCount;
    int nodeCount;
    int v1, v2, weight;
    std::string line;
    std::ifstream file(filename);

    if (file.good()) {
        file >> edgeCount >> nodeCount;

        switch (type) {
            case (GraphType::MATRIX):
                graph = new MatrixGraph(nodeCount, edgeCount);
                break;
            case (GraphType::NEIGHBOURS_LIST):
                graph = new NListGraph(nodeCount, edgeCount);
                break;
            default:
                std::cout << "Chosen graph type does not exist";
                return graph;
        }

        for (int i = 0; i < edgeCount; i++) {
            file >> v1 >> v2 >> weight;
            graph->addEdge(v1, v2, weight);
        }

        file.close();
    } else {
        std::cout << "File error - OPEN" << std::endl;
    }
    return graph;
}

FileReader::FileReader() {}

FileReader::~FileReader() {

}
