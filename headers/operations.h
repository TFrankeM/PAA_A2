#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H
#include <vector>

#include "structure.h"

using namespace std;

// Classe GraphOperations para realizar operações no grafo
class GraphOperations {
public:
    // Encontra os n entregadores mais próximos de um dado vértice
    static vector<pair<DeliveryPerson, int>> findNearestDeliveryPeople(GraphAdjList& graph, Order order, int numDeliveryPeople);

    // Encontra a rota mais curta a partir de uma ordem e do entregador
    vector<EdgeNode*> defineSimpleDeliveryRoute(GraphAdjList& graph, Order order, DeliveryPerson deliveryPerson);
    
    // funcao auxiliar para encontrar rota mais curta entre dois pontos
    vector<Vertex> findPath(GraphAdjList& graph, Vertex startVertex, Vertex endVertex);

    // funcao auxiliar para juntar sub-rotas menores da rota final
    void addToRoute(GraphAdjList& graph, vector<EdgeNode*>& route, vector<Vertex> path);


};

#endif

