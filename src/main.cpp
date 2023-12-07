#include <iostream>
#include "../headers/structure.h"

using namespace std;

typedef int vertex;

int main()
{
    GraphAdjList g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 2);
    g.addEdge(4, 1, 1);
    g.print();
}

