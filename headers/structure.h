#include <iostream>
#include "client.h"
#include "deliveryperson.h"
#include "distributioncenter.h"
#include "seller.h"

using namespace std;

// Cria o tipo "vertex" que é um inteiro
class Vertex
{
private:
    int id;
    vector<Client> clients;
    vector<DeliveryPerson> deliveryPeople;
    vector<DistributionCenter> distributionCenters;
    vector<Seller> sellers;

public:
    Vertex(int id); // Construtor
    int getId();    // Retorna o id do vértice
    void addClient(const Client& client); // Adiciona um cliente
    void addDeliveryPerson(const DeliveryPerson& deliveryPerson); // Adiciona um entregador
    void addDistributionCenter(const DistributionCenter& distributionCenter); // Adiciona um centro de distribuição
    void addSeller(const Seller& seller); // Adiciona um vendedor
    vector<Client> getClients(); // Retorna a lista de clientes
    vector<DeliveryPerson> getDeliveryPeople(); // Retorna a lista de entregadores
    vector<DistributionCenter> getDistributionCenters(); // Retorna a lista de centros de distribuição
    vector<Seller> getSellers(); // Retorna a lista de vendedores
};

/* EdgeNode Header*/
class EdgeNode
{
private:
    Vertex m_otherVertex;
    EdgeNode* m_next;
    int m_length;

public:
    EdgeNode(Vertex m_otherVertex, EdgeNode* m_next, int m_length); // Construtor
    Vertex otherVertex();           // Retorna o vértice de destino
    EdgeNode* getNext();            // Retorna o próximo nó
    int getLength();                // Retorna o comprimento da aresta
    void setNext(EdgeNode* next);   // Atribui o próximo nó
};


/* GraphAdjList Header*/
class GraphAdjList
{
private:
    int m_numVertices;
    int m_numEdges;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices);                  // Construtor
    ~GraphAdjList();                                // Destrutor
    void addEdge(int id_v1, int id_v2, int length); // Adiciona uma aresta
    void removeEdge(int id_v1, int id_v2);          // Remove uma aresta
    void print();                                   // Imprime o grafo
};

