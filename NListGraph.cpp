#include "NListGraph.h"
#include "Heap.h"
#include "TabUtils.h"


NListGraph::NListGraph(int nodes, bool verbose) : NListGraph(nodes) {
    _verbose = verbose;
}

int NListGraph::getNodesCount() {
    return _nodes;
}

NListGraph::NListGraph(int nodes) :_nodes(nodes) {
    _neighbours = new NList *[nodes];
    kruskalHelper = new KruskalHelper(nodes);
    NList *tab;
    for (int i = 0; i < nodes; i++) {
        _neighbours[i] = new NList();
    }
}

NListGraph::~NListGraph() {
    for (int i = 0; i < _nodes; ++i) {
        delete _neighbours[i];
    }
    delete _neighbours;
    delete kruskalHelper;
}

void NListGraph::addEdge(int v1, int v2, int weight) {
    _neighbours[v1]->pushFront(v2, weight);
    _edges += 1;
}

void NListGraph::print() {
    if (_neighbours == nullptr) {
        std::cout << "Graph is empty\n";
        return;
    }
    std::cout << "\nVertices: " << _nodes << ", Edges: " << _edges;
    std::cout << "\nNeighbours list: \n";
    for(int i = 0; i < _nodes; i++)
    {
        std::cout << i << " -> { ";
        _neighbours[i]->print();
        std::cout << " }\n";
    }
}

void NListGraph::dijkstra(int startingVerticle) {
    int searched[_nodes];                                  //zbiór wierzchołków grafu o policzonych już najkrótszych ścieżkach od wybranego wierzchołka v
    int queue[_nodes];                                     //zbiór wierzchołków grafu, dla których najkrótsze ścieżki nie zostały jeszcze policzone
    int damage[_nodes];                                    //tablica na koszty dojścia (damage jako koszt takie tłumaczenie)
    int previous[_nodes];                                  //tablica poprzedników na ścieżkach
    int u,w = 0;                                           //wierzchołki u i w na  których wykonywane są operacje

    for(int i=0; i < _nodes; i++){                         //Inicjalizacja zbiorów
        searched[i] = INT_MAX;                             //Ustawienie zbioru size jako pustego
        queue[i] = i;                                      //Wpisanie wszystkich wierzchołków grafu do kolejki queue
        damage[i] = INT_MAX;                               //Wypełnienie tablicy damage największą wartościa dodatnią
        previous[i] = -1;                                  //wypełnienie tablicy previous wartością -1 oznaczającą brak poprzednika
    }

    damage[startingVerticle] = 0;                          //koszt dojścia do wierzchołka startowego jest zerowy

    while(!TabUtils::isEmpty(queue, _nodes)){
        u = TabUtils::lowestValueInTab(damage, queue, _nodes);
        searched[u] = u;
        queue[u] = INT_MAX;

        for(int i = 0; i < _neighbours[u]->getSize(); i++){      //Petla iterujaca po wszystkich sasiadach
            w = _neighbours[u]->get(i);
            if (!TabUtils::inQueue(queue, w)) continue;         //sprawdź czy wierzchołek w jest w kolejce
            if(damage[w] <=  (damage[u]+ _neighbours[u]->getWeight(i))) continue;
            damage[w] = damage[u] + _neighbours[u]->getWeight(i);
            previous[w] = u;
        }
    }

    if(!_verbose) return;

    std::cout << "Algorytm Dijkstry - Lista Sasiedztwa" << std::endl;
    for(int i=0; i < _nodes; i++){
        u = i;
        std::cout << "Dojscie do wierzcholka " << i << ": ";
        while (previous[u] != -1){
            std::cout << u << "-";
            u = previous[u];
        }
        std::cout << startingVerticle << ", koszt: " << damage[i] << std::endl;
    }
    std::cout << std::endl;
}

void NListGraph::bellmanFord(int startingVerticle) {
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
            for (y = 0; y < _neighbours[x]->getSize(); y++){
                if (_neighbours[x]->get(y) == startingVerticle) continue;
                if (damage[_neighbours[x]->get(y)] <= damage[x] + _neighbours[x]->getWeight(y)) continue;
                if (damage[x] == INT_MAX) continue;
                change = false;
                damage[_neighbours[x]->get(y)] = damage[x] + _neighbours[x]->getWeight(y);
                previous[_neighbours[x]->get(y)] = x;
            }
        }
        if (change) break;
    }

    if(!change) {
        for (x = 0; x < _nodes; x++) {
            for (y = 0; y < _neighbours[x]->getSize(); y++) {
                if (damage[_neighbours[x]->get(y)] > damage[x] + _neighbours[x]->getWeight(y)) {
                    std::cout << "Wykryto ujemny cykl!";
                    return;
                }
            }
        }
    }

    if(!_verbose) return;

    std::cout << std::endl;
    for (int i = 0; i < _nodes; i++) {
        std::cout << damage[i] << " | ";
    }
    std::cout << std::endl;
    for (int i = 0; i < _nodes; i++) {
        std::cout << previous[i] << " | ";
    }
    std::cout << std::endl;
    std::cout << "Algorytm Bellmana-Forda - Lista Sasiedztwa" << std::endl;
    for(int i=0; i < _nodes; i++){
        u = i;
        std::cout << "Dojscie do wierzcholka " << i << ": ";
        while (previous[u] != -1){
            std::cout << u << "-";
            u = previous[u];
        }
        std::cout << startingVerticle << ", koszt: " << damage[i] << std::endl;
    }
    std::cout << std::endl;

}

void NListGraph::kruskal() {
    auto edgesSorted = new Heap();
    for(int i = 0; i < _nodes; i++){
        for(int j = 0; j < _neighbours[i]->getSize(); j++){
            auto edge = Edge();
            edge.v1 = i;
            edge.v2 = _neighbours[i]->get(j);
            edge.weight = _neighbours[i]->getWeight(j);
            edgesSorted->add(edge);
        }
    }

    this->kruskalHelper->findMST(edgesSorted, _verbose);

    delete edgesSorted;
}

void NListGraph::prim(int startingVerticle) {
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
            auto neighbourInQueue = queue.find(neighbourVertex);

            if (neighbourInQueue < 0)
                continue;

            auto currentVertexToNeighbourIndex = _neighbours[currentVertex]->find(neighbourVertex);
            auto neighbourToCurrentVertexIndex = _neighbours[neighbourVertex]->find(currentVertex);

            auto currentVertexToNeighbour = currentVertexToNeighbourIndex != -1 ? _neighbours[currentVertex]->getWeight(currentVertexToNeighbourIndex) : INT_MAX;
            auto neighbourToCurrentVertex = neighbourToCurrentVertexIndex != -1 ? _neighbours[neighbourVertex]->getWeight(neighbourToCurrentVertexIndex) : INT_MAX;

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

    if(!_verbose) return;
    const int numberWidth = 3;
    std::cout << std::endl;

    std::cout << "Wierzcholek: ";
    for(int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << i << "  ";
    }
    std::cout << std::endl;

    std::cout << "Poprzednik:  ";
    for(int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << previous[i] << "  ";
    }
    std::cout << std::endl;

    int cost = 0;

    std::cout << "Koszt:       ";
    for(int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << costs[i] << "  ";
        cost += costs[i];
    }
    std::cout << std::endl;

    std::cout << "Sumaryczny koszt: " << cost << std::endl;
}

bool NListGraph::isConnected() {
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

        _neighbours[u]->foreach([&visited, &q](int v) {
            if(!visited[v]) {
                visited[v] = true;
                q.pushEnd(v);
            }
        });
    }

    // Sprawdzanie, czy wszystkie wierzchołki są osiągalne
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }

    return true;
}

bool NListGraph::edgeExists(int v1, int v2) {
    if(v1 < 0 || v1 >= _nodes || v2 < 0 || v2 >= _nodes)
        return false;

    return _neighbours[v1]->find(v2) != -1;
}
