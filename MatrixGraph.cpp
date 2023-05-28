#include "MatrixGraph.h"
#include <iostream>
#include "TabUtils.h"

MatrixGraph::MatrixGraph(int nodes, bool verbose, int **innerMatrix) {
    _innerMatrix = innerMatrix;
    _nodes = nodes;
    _verbose = verbose;
    kruskalHelper = new KruskalHelper(nodes);
}

MatrixGraph::MatrixGraph(int nodes, bool verbose) : MatrixGraph(nodes) {
    _verbose = verbose;
}

int MatrixGraph::getNodesCount() {
    return _nodes;
}

MatrixGraph::MatrixGraph(int nodes) : _nodes(nodes) {
    _innerMatrix = new int *[nodes];
    int *tab;
    for (int i = 0; i < nodes; i++) {
        tab = new int[nodes];
        _innerMatrix[i] = new int[nodes];
        for (int j = 0; j < nodes; j++) {
            tab[j] = INT_MAX;
            _innerMatrix[i][j] = INT_MAX;
        }
        _innerMatrix[i] = tab;
    }
    kruskalHelper = new KruskalHelper(nodes);
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < _nodes; i++) {
        delete[] _innerMatrix[i];
    }
    delete[] _innerMatrix;
    _innerMatrix = nullptr;
    delete kruskalHelper;
}

void MatrixGraph::addEdge(int v1, int v2, int weight) {
    _innerMatrix[v1][v2] = weight;
    _edges += 1;
}

void MatrixGraph::print() {
    if (_innerMatrix == nullptr) {
        std::cout << "Graph is empty" << std::endl;
        return;
    }
    std::cout << "\nVertices: " << _nodes << ", Edges: " << _edges;
    std::cout << "\nAdjacency matrix: " << std::endl;
    std::cout << "  ";
    for (int i = 0; i < _nodes; i++) {
        if (i > 10) std::cout << " ";
        else std::cout << "  ";
        std::cout << i;
    }
    std::cout << "\n" << std::endl;
    for (int i = 0; i < _nodes; i++) {
        std::cout << i;
        if (i < 10) std::cout << " ";
        for (int j = 0; j < _nodes; j++) {
            if (j > 0) {
                if (_innerMatrix[i][j - 1] >= 10) std::cout << " ";
                else std::cout << "  ";
            } else std::cout << "  ";
            if (_innerMatrix[i][j] == INT_MAX) {
                std::cout << "x ";
            } else {
                std::cout << _innerMatrix[i][j];
            }
        }
        std::cout << std::endl;
    }
}

void MatrixGraph::bellmanFord(int startingVerticle) {
    int damage[_nodes];
    int previous[_nodes];
    bool change;
    int x,y,u;

    for(int i=0; i < _nodes; i++){
        damage[i] = INT_MAX;                               //Wypełnienie tablicy damage największą wartościa dodatnią
        previous[i] = -1;                                  //wypełnienie tablicy previous wartością -1 oznaczającą brak poprzednika
    }

    damage[startingVerticle] = 0;

    for (int n = 1; n < _nodes; n++){
        change = true;
        for (x = 0; x < _nodes; x++){
            for (y = 0; y < _nodes; y++){
                if (y == startingVerticle) continue;
                if (_innerMatrix[x][y] == INT_MAX) continue;
                if (damage[y] <= damage[x] + _innerMatrix[x][y]) continue;
                if (damage[x] == INT_MAX) continue;
                change = false;
                damage[y] = damage[x] + _innerMatrix[x][y];
                previous[y] = x;
            }
        }
        if (change) break;
    }

    if(!change) {
        for (x = 0; x < _nodes; x++) {
            for (y = 0; y < _nodes; y++) {
                if (_innerMatrix[x][y] == INT_MAX) continue;
                if (damage[y] > damage[x] + _innerMatrix[x][y]) {
                    std::cout << "Wykryto ujemny cykl!";
                    return;
                }
            }
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < _nodes; i++) {
        std::cout << damage[i] << " | ";
    }
    std::cout << std::endl;
    for (int i = 0; i < _nodes; i++) {
        std::cout << previous[i] << " | ";
    }
    std::cout << std::endl;
    std::cout << "Algorytm Bellmana-Forda - Macierz" << std::endl;
    for (int i = 0; i < _nodes; i++) {
        u = i;
        std::cout << "Dojscie do wierzcholka " << i << ": ";
        while (previous[u] != -1) {
            std::cout << u << "-";
            u = previous[u];
        }
        std::cout << startingVerticle << ", koszt: " << damage[i] << std::endl;
    }
    std::cout << std::endl;

}

void MatrixGraph::kruskal() {
    auto edgesSorted = new Heap();
    for (int i = 0; i < _nodes; i++) {
        for (int j = 0; j < _nodes; j++) {
            auto edge = Edge();
            edge.v1 = i;
            edge.v2 = j;
            edge.weight = _innerMatrix[i][j];
            edgesSorted->add(edge);
        }
    }

    this->kruskalHelper->findMST(edgesSorted, _verbose);

    delete edgesSorted;
}

void MatrixGraph::prim(int startingVerticle) {
    int costs[_nodes];
    int previous[_nodes];

    for (int i = 0; i < _nodes; i++) {
        costs[i] = INT_MAX; // infinity
        previous[i] = -1; // unreached
    }

    costs[startingVerticle] = 0; // cost of staying at starting point

    auto queue = LinkedList();

    for (int i = 0; i < _nodes; i++) {
        queue.pushEnd(i);
    }

    while (!queue.isEmpty()) {
        int currentVertex = -1;

        queue.foreach([&costs, &currentVertex](int x) {
            if (costs[x] != INT_MAX && (currentVertex == -1 || costs[x] < costs[currentVertex])) {
                currentVertex = x;
            }
        });
        if(currentVertex == -1) break;

        for (int neighbourVertex = 0; neighbourVertex < _nodes; neighbourVertex++) {
            if (_innerMatrix[currentVertex][neighbourVertex] == INT_MAX && _innerMatrix[neighbourVertex][currentVertex] == INT_MAX)
                continue;

            auto neighbourInQueue = queue.find(neighbourVertex);

            if (neighbourInQueue < 0)
                continue;

            auto currentVertexToNeighbour = _innerMatrix[currentVertex][neighbourVertex];
            auto neighbourToCurrentVertex = _innerMatrix[neighbourVertex][currentVertex];

            if (costs[neighbourVertex] > currentVertexToNeighbour && currentVertexToNeighbour <= neighbourToCurrentVertex) {
                costs[neighbourVertex] = currentVertexToNeighbour;
                previous[neighbourVertex] = currentVertex;
                continue;
            }

            if (costs[neighbourVertex] > neighbourToCurrentVertex) {
                costs[neighbourVertex] = neighbourToCurrentVertex;
                previous[neighbourVertex] = currentVertex;
            }
        }

        queue.remove(queue.find(currentVertex));
    }

    if (!_verbose) return;
    const int numberWidth = 3;
    std::cout << std::endl;

    std::cout << "Wierzcholek: ";
    for (int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << i << "  ";
    }
    std::cout << std::endl;

    std::cout << "Poprzednik:  ";
    for (int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << previous[i] << "  ";
    }
    std::cout << std::endl;

    int cost = 0;

    std::cout << "Koszt:       ";
    for (int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << costs[i] << "  ";
        cost += costs[i];
    }
    std::cout << std::endl;

    std::cout << "Sumaryczny koszt: " << cost << std::endl;
}


void MatrixGraph::dijkstra(int startingVerticle) {
    int searched[_nodes];                                  //zbiór wierzchołków grafu o policzonych już najkrótszych ścieżkach od wybranego wierzchołka v
    int queue[_nodes];                                     //zbiór wierzchołków grafu, dla których najkrótsze ścieżki nie zostały jeszcze policzone
    int damage[_nodes];                                    //tablica na koszty dojścia (damage jako koszt takie tłumaczenie)
    int previous[_nodes];                                  //tablica poprzedników na ścieżkach
    int u, w = 0;                                           //wierzchołki u i w na  których wykonywane są operacje

    for (int i = 0; i < _nodes; i++) {                         //Inicjalizacja zbiorów
        searched[i] = INT_MAX;                             //Ustawienie zbioru size jako pustego
        queue[i] = i;                                      //Wpisanie wszystkich wierzchołków grafu do kolejki queue
        damage[i] = INT_MAX;                               //Wypełnienie tablicy damage największą wartościa dodatnią
        previous[i] = -1;                                  //wypełnienie tablicy previous wartością -1 oznaczającą brak poprzednika
    }

    damage[startingVerticle] = 0;                          //koszt dojścia do wierzchołka startowego jest zerowy

    while (!TabUtils::isEmpty(queue, _nodes)) {
        u = TabUtils::lowestValueInTab(damage, queue, _nodes);
        searched[u] = u;
        queue[u] = INT_MAX;

        for (int i = 0; i < _nodes; i++) {                   //Sprawdzenie wszytkich wierzchołków w poszukiwaniu sąsiadów
            if (_innerMatrix[u][i] == INT_MAX) continue;    //Sprawdzenie sąsiedztwa
            w = i;
            if (!TabUtils::inQueue(queue, w)) continue;    //sprawdź czy wierzchołek w jest w kolejce
            if (damage[w] <= (damage[u] + _innerMatrix[u][w])) continue;
            damage[w] = damage[u] + _innerMatrix[u][w];
            previous[w] = u;
        }
    }

    if (!_verbose) return;
    std::cout << std::endl;
    std::cout << "Algorytm Dijkstry - Macierz" << std::endl;
    for (int i = 0; i < _nodes; i++) {
        u = i;
        std::cout << "Dojscie do wierzcholka " << i << ": ";
        while (previous[u] != -1) {
            std::cout << u << "-";
            u = previous[u];
        }
        std::cout << startingVerticle << ", koszt: " << damage[i] << std::endl;
    }
    std::cout << std::endl;
}

bool MatrixGraph::isConnected() {
    bool visited[_nodes];
    for(int i = 0; i < _nodes; ++i) {
        visited[i] = false;
    }

    LinkedList q;

    // Przeszukiwanie wszerz od pierwszego wierzchołka
    q.pushEnd(0);
    visited[0] = true;

    while (!q.isEmpty()) {
        int u = q.get(0);
        q.removeFront();

        for(int v = 0; v < _nodes; ++v) {
            if (_innerMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                q.pushEnd(v);
            }
        }
    }

    // Sprawdzanie, czy wszystkie wierzchołki są osiągalne
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }

    return true;
}

bool MatrixGraph::edgeExists(int v1, int v2) {
    if(v1 < 0 || v1 >= _nodes || v2 < 0 || v2 >= _nodes)
        return false;

    return _innerMatrix[v1][v2] != INT_MAX;
}
