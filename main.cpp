#include <iostream>
#include "FileReader.h"
#include "Generator.h"
#include "Tests.h"

using namespace std;

int main() {

    /*
    auto graphM = FileReader::loadGraphFromFile("C:/Users/user/SdizoProjekt2/test.txt", GraphType::MATRIX);
    auto graphN = FileReader::loadGraphFromFile("C:/Users/user/SdizoProjekt2/test.txt", GraphType::NEIGHBOURS_LIST);
    graphM->bellmanFord(4);
    graphM->dijkstra(4);
    */


    //auto testing = Tests();
    //testing.listTests();
    //testing.matrixTests();


    int choice;
    string filename;
    int startingVerticle = 0;
    Graph *graphN = nullptr;
    Graph *graphM = nullptr;

    do {
        cout << endl;
        cout << "==== Load From File ====" << endl;
        cout << "Enter the file name:" << endl;
        cin >> filename;
        cout << endl;
        graphN = FileReader::loadGraphFromFile(filename, GraphType::NEIGHBOURS_LIST);
        graphM = FileReader::loadGraphFromFile(filename, GraphType::MATRIX);
    }while(graphN == nullptr || graphM == nullptr);

    do{
        cout << endl;
        cout << "==== MAIN MENU ====" << endl;
        cout << "1.Display Graph as Matrix and Neighbours List" << endl;
        cout << "2.Kruskal's Algorithm" << endl;
        cout << "3.Prim's Algorithm" << endl;
        cout << "4.Dijkstra's Algorithm" << endl;
        cout << "5.Bellman-Ford's Algorithm" << endl;
        cout << "0.Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                graphN->print();
                graphM->print();
                break;

            case 2:
                graphN->kruskal();
                graphM->kruskal();
                break;

            case 3:
                graphN->prim(startingVerticle);
                graphM->prim(startingVerticle);
                break;

            case 4:
                graphN->dijkstra(startingVerticle);
                graphM->dijkstra(startingVerticle);
                break;

            case 5:
                graphN->bellmanFord(startingVerticle);
                graphM->bellmanFord(startingVerticle);
                break;

            default:
                break;
        }
    }while(choice != 0);

    return 0;
}
