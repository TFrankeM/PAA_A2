#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include "../headers/structure.h"
#include <vector>

using namespace std;

// Classe GraphOperations para realizar operações no grafo
class GraphOperations {
public:
    // Encontra os n entregadores mais próximos de um dado vértice
    static vector<pair<int, int>> findNearestDeliveryPeople(GraphAdjList& graph, int startVertexId, int numDeliveryPeople);

    // Mais operações
};

#endif

