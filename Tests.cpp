#include "Tests.h"
#include <map>
#include "Generator.h"
#include "Timer.h"
#include "WriteToFile.h"

void Tests::listTests()
{
    for(int i = 10; i <= 50; i += 10) {
        gpTest(GraphType::NEIGHBOURS_LIST, i, 100);
    }
}

void Tests::matrixTests()
{
    for(int i = 10; i <= 50; i += 10) {
        gpTest(GraphType::MATRIX, i, 100);
    }
}

void Tests::gpTest(GraphType type, int nodes, int retries) {
    std::map<double, double> primTimes;
    std::map<double, double> kruskalTimes;
    std::map<double, double> dijkstraTimes;
    std::map<double, double> bellmanFordTimes;

    for(int i = 1; i <= 4; ++i) {
        Graph *graph;
        if(type == GraphType::MATRIX) {
            graph = Generator::createMatrix(nodes, i * 25, 2 * nodes, false);
        } else {
            graph = Generator::generate(nodes, i * 0.25, type, false);
        }

        std::cout << "PRIM" << std::endl;
        auto primTime = primTests(graph, retries);
        primTimes[i * 0.25] = primTime;

        std::cout << "KRUSKAL" << std::endl;
        auto kruskalTime = kruskalTests(graph, retries);
        kruskalTimes[i * 0.25] = kruskalTime;

        std::cout << "DIJKSTRA" << std::endl;
        auto dijkstraTime = dijkstraTests(graph, retries);
        dijkstraTimes[i * 0.25] = dijkstraTime;

        std::cout << "FORD" << std::endl;
        auto bellmanFordTime = bellmanFordTests(graph, retries);
        bellmanFordTimes[i * 0.25] = bellmanFordTime;

        delete graph;
    }

    std::string typeName = graphTypeString[type];
    std::string nodesCountString = std::to_string(nodes);
    WriteToFile::saveMapToFile(typeName + "_" + nodesCountString + "_prim.csv", primTimes);
    WriteToFile::saveMapToFile(typeName + "_" + nodesCountString + "_kruskal.csv", kruskalTimes);
    WriteToFile::saveMapToFile(typeName + "_" + nodesCountString + "_dijkstra.csv", dijkstraTimes);
    WriteToFile::saveMapToFile(typeName + "_" + nodesCountString + "_bellmanFord.csv", bellmanFordTimes);
}

double Tests::primTests(Graph *graph, int retries) {
    double time = 0;
    Timer timer{};

    for(int i = 0; i < retries; ++i) {
        timer.start();
        graph->prim(0);
        time += timer.getElapsedTime_ms();
    }

    return time / retries;
}

double Tests::kruskalTests(Graph *graph, int retries) {
    double time = 0;
    Timer timer{};

    for(int i = 0; i < retries; ++i) {
        timer.start();
        graph->kruskal();
        time += timer.getElapsedTime_ms();
    }

    return time / retries;
}

double Tests::dijkstraTests(Graph *graph, int retries) {
    double time = 0;
    Timer timer{};

    for(int i = 0; i < retries; ++i) {
        timer.start();
        graph->dijkstra(0);
        time += timer.getElapsedTime_ms();
    }

    return time / retries;
}

double Tests::bellmanFordTests(Graph *graph, int retries) {
    double time = 0;
    Timer timer{};

    for(int i = 0; i < retries; ++i) {
        timer.start();
        graph->bellmanFord(0);
        time += timer.getElapsedTime_ms();
    }

    return time / retries;
}