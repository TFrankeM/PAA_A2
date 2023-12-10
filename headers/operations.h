#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include "distributioncenter.h"
#include "structure.h"
#include "minheap.h"
#include "maxheap.h"
#include "order.h"
#include <vector>


using namespace std;



struct Route {
    int id;
    Order order;
    vector<EdgeNode*> route;
    DeliveryPerson deliveryPerson;
    DistributionCenter distributionCenter;

    // Construtor
    Route(const int id, const Order& order, const vector<EdgeNode*>& route, DeliveryPerson deliveryPerson, DistributionCenter distributionCenter);

    // Métodos
    int getId() const;
    void changeRoute(const vector<EdgeNode*>& newRoute);
    const Order& getOrder() const;
    const DistributionCenter& getDistributionCenter() const;
    const DeliveryPerson& getDeliveryPerson() const;
};

// Classe GraphOperations para realizar operações no grafo
class GraphOperations {
public:
    //////////////////////////////////////////////////////// 1 ////////////////////////////////////////////////////////

    // Encontra os n entregadores mais próximos de um dado vértice
    static vector<pair<DeliveryPerson, float>> findNearestDeliveryPeople(GraphAdjList& graph, Order order, int numDeliveryPeople);

    //////////////////////////////////////////////////////// 2 ////////////////////////////////////////////////////////

    // Encontra a rota mais curta a partir de uma ordem e do entregador
    vector<EdgeNode*> defineSimpleDeliveryRoute(GraphAdjList& graph, Order order, DeliveryPerson deliveryPerson);
    
    // funcao auxiliar para encontrar rota mais curta entre dois pontos
    vector<Vertex*> findPath(GraphAdjList& graph, Vertex* startVertex, Vertex* endVertex);

    // funcao auxiliar para juntar sub-rotas menores da rota final
    void addToRoute(GraphAdjList& graph, vector<EdgeNode*>& route, vector<Vertex*> path);

    //////////////////////////////////////////////////////// 3 ////////////////////////////////////////////////////////

    // Função que busca os n entregadores cujas rotas apresentem a menor distância total passando por algum 
    // centro de distribuição que contém o produto no seu inventário
    vector<Path> findBestDeliveryRoutes(GraphAdjList& graph, 
                                        const Order& order, 
                                        const vector<DistributionCenter>& distributionCenters, 
                                        int numDeliveryPeople);

    // Função para calcular as distâncias dos entregadores usando o algoritmo de Dijkstra
    vector<Path> calculatesDijkstraDistance(GraphAdjList& graph, 
                                           int centroDistribuicaoID, 
                                           int centerAddress, 
                                           int numDeliveryPeople,
                                           int clientAddress);

    // Função para reconstruir uma rota a partir dos pais dos vértices
    vector<int> reconstruirRota(const vector<Vertex*>& parents, Vertex* vertex, Vertex* centerVertex); 

    //////////////////////////////////////////////////////// 4 ////////////////////////////////////////////////////////

    // funcoes auxiliares
    vector<Order> filterOrdersByAvailability(const vector<Order> orders, const DistributionCenter& distributionCenter);

    bool orderByPricePerWeight(const Order a, const Order b);

    vector<Order> getMaxPriceOrdersLimitedByCenter(const vector<Order> orders, double weightLimit);

    vector<Order> findOrdersSugest(GraphAdjList& graph, Route& route);

    // funcao auxiliar que calcula sugestao de outras entregas com base no faturamento 
    // nao considera custo, apenas a capacidade do delivery
    std::pair<double, double> calculateTotalPriceAndWeight(const vector<Order>& orders);
};
#endif

