#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include "../headers/distributioncenter.h"
#include "../headers/structure.h"
#include "../headers/minheap.h"
#include "../headers/maxheap.h"
#include "../headers/order.h"
#include <vector>


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

    // Função que busca os n entregadores cujas rotas apresentem a menor distância total passando por algum 
    // centro de distribuição que contém o produto no seu inventário
    vector<Path> findBestDeliveryRoutes(GraphAdjList& graph, 
                                        vector<DistributionCenter>& distributionCenters, 
                                        Order order, 
                                        int numDeliveryPeople);
};

#endif

