cmake_minimum_required(VERSION 3.23)
project(SdizoProjekt2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(SdizoProjekt2 main.cpp FileReader.cpp FileReader.h MatrixGraph.cpp MatrixGraph.h NListGraph.cpp NListGraph.h ArrayList.cpp ArrayList.h DList.cpp DList.h Heap.cpp Heap.h LinkedList.cpp LinkedList.h NList.cpp NList.h TabUtils.cpp TabUtils.h KruskalHelper.cpp KruskalHelper.h Graph.h Generator.cpp Generator.h WriteToFile.cpp WriteToFile.h Tests.cpp Tests.h Timer.cpp Timer.h)
