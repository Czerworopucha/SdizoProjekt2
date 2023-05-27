#include "NListGraph.h"
#include "Heap.h"

NListGraph::NListGraph(int nodes, int edges) :_nodes(nodes), _edges(edges) {
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
    //_neighbours[v2]->pushFront(v1, weight);
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

    for (int i = 0; i < _nodes; i++) {
        std::cout << damage[i] << " | ";
    }
    std::cout << std::endl;
    for (int i = 0; i < _nodes; i++) {
        std::cout << previous[i] << " | ";
    }

    for(int i=0; i < _nodes; i++){
        u = i;
        std::cout << "Dojscie do wierzcholka " << i << ": ";
        while (previous[u] != -1){
            std::cout << u << "-";
            u = previous[u];
        }
        std::cout << startingVerticle << ", koszt: " << damage[i] << std::endl;
    }

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

    this->kruskalHelper->findMST(edgesSorted);

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

        for (int neighbourVertex = 0; neighbourVertex < _nodes; neighbourVertex++) {
            if (!queue.contains(neighbourVertex))
                continue;

            auto neighbourIndex = _neighbours[currentVertex]->find(neighbourVertex);
            if (neighbourIndex == -1)
                continue;

            auto neighbourWeight = _neighbours[currentVertex]->getWeight(neighbourIndex);
            if (costs[neighbourVertex] <= neighbourWeight)
                continue;

            costs[neighbourVertex] = neighbourWeight;
            previous[neighbourVertex] = currentVertex;
        }

        queue.remove(queue.find(currentVertex));
    }
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

    std::cout << "Koszt:       ";
    for(int i = 0; i < _nodes; ++i) {
        std::cout << std::setw(numberWidth) << costs[i] << "  ";
    }
    std::cout << std::endl;
}

void NListGraph::fordFulkerson(int startingVerticle) {

}