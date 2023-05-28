#include "Generator.h"
#include <random>
#include "MatrixGraph.h"
#include "NListGraph.h"

Graph* Generator::generate(int nodes, double density, GraphType type, bool verbose)
{
    Graph *graph = nullptr;
    switch (type) {
        case (GraphType::MATRIX):
            graph = new MatrixGraph(nodes, verbose);
            break;
        case (GraphType::NEIGHBOURS_LIST):
            graph = new NListGraph(nodes, verbose);
            break;
        default:
            std::cout << "Chosen graph type does not exist";
            return graph;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::uniform_real_distribution<> weightsDist(1, 20);

    for (int u = 0; u < nodes; ++u) {
        for (int v = 0; v < nodes; ++v) {
            if (u != v && dis(gen) < density) {
                graph->addEdge(u, v, (int)weightsDist(gen));
            }
        }
    }

    while (!graph->isConnected()) {
        int u = 0;
        int v = 0;

        // Wyszukiwanie pierwszej pary wierzchołków, które nie mają krawędzi między nimi
        bool found = false;
        for (; u < nodes; ++u) {
            for (v = u + 1; v < nodes; ++v) {
                if (!graph->edgeExists(u, v)) {
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }

        // Dodawanie brakującej krawędzi
        graph->addEdge(u, v,(int)weightsDist(gen));
    }

    return graph;
}

MatrixGraph* Generator::createMatrix(int nodes, double edgesPercent, int maxEdges, bool verbose) {
    auto edges = maxEdges * (edgesPercent / 100);

    bool found;
    int counter = nodes;
    int begin, end;
    int *visited = new int[nodes];
    auto matrix = new int *[nodes];
    for (int i = 0; i < nodes; i++) {
        visited[i] = 0;
        matrix[i] = new int[nodes];
        for (int j = 0; j < nodes; j++) {
            matrix[i][j] = INT_MAX;
        }
    }
    spTree(matrix, nodes, visited);
    while (counter <= edges) {
        found = false;
        begin = rand() % nodes;
        for (int i = 0; i < nodes; i++) {
            if (i != begin && matrix[begin][i] == INT_MAX) {
                found = true;
                end = i;
            }
        }
        if (!found) continue;
        matrix[begin][end] = (rand() % 99) + 1;
        counter++;
    }
    delete[] visited;

    return new MatrixGraph(nodes, verbose, matrix);
}

//Funkcja towrzaca drzewo rozpinajace dla nieskierowanego
void Generator::spTree(int **matrix, int nodes, int *visited) {
    bool check = true;
    int created = 1;
    int node = 0;
    int children, count, temp, rr;
    visited[node] = 1;
    do {
        count = 0;
        children = (rand() % 2) + 2;
        do {
            if (created == nodes) return;
            temp = rand() % nodes;
            if (temp == (node)) continue;
            if (visited[temp] != 0) continue;
            else {
                matrix[node][temp] = (rand() % 99) + 1;
                visited[temp] = 1;
            }
            count++;
            created++;
        } while (count != children);
        while (true) {
            rr = rand() % nodes;
            if (visited[rr] == 1) {
                for (int j = 1; j < nodes; j++) {
                    if (matrix[rr][j] != INT_MAX) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    node = rr;
                    break;
                } else check = true;
            }
        }
    } while (created != nodes);
}