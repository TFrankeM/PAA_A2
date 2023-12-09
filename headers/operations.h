#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include "../headers/structure.h"
#include <vector>

using namespace std;

// Classe GraphOperations para realizar operações no grafo
class GraphOperations {
public:
    // Encontra os n entregadores mais próximos de um dado vértice
    static vector<pair<int, int>> findNearestDeliveryPeople(GraphAdjList& graph, Order order, int numDeliveryPeople);

    // Encontra a rota mais curta a partir de uma ordem e do entregador
    vector<EdgeNode*> defineSimpleDeliveryRoute(GraphAdjList& graph,Order order, int DeliveryPersonId);
    
    // funcao auxiliar para encontrar rota mais curta entre dois pontos
    vector<int> findPath(GraphAdjList& graph, int startVertexId, int endVertexId);

    // funcao auxiliar para juntar sub-rotas menores da rota final
    void addToRoute(GraphAdjList& graph, vector<EdgeNode*>& route, vector<int> path);


};

#endif

