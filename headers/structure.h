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
    float m_length;

public:
    EdgeNode(Vertex m_otherVertex, EdgeNode* m_next, float m_length); // Construtor
    Vertex otherVertex();           // Retorna o vértice de destino
    EdgeNode* getNext();            // Retorna o próximo nó
    float getLength();                // Retorna o comprimento da aresta
    void setNext(EdgeNode* next);   // Atribui o próximo nó
};


/* GraphAdjList Header*/
class GraphAdjList
{
private:
    int m_numVertices;
    int m_numEdges;
    vector<Product> m_products;
    vector<Client> m_clients;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices);                    // Construtor
    ~GraphAdjList();                                  // Destrutor
    
    Vertex getVertex(int id);                         // Retorna um vértice
    int getNumVertices();                             // Retorna o número de vértices
    
    void addEdge(int id_v1, int id_v2, float length);     // Adiciona uma aresta
    void removeEdge(int id_v1, int id_v2);                // Remove uma aresta
    EdgeNode* getEdges(int id);                           // Retorna as arestas de um vértice
    int getNumEdges();                                    // Retorna o número de arestas
    
    void addVertex(int id_v1, int id_v2, float distance); // Adiciona um vértice no meio de uma aresta

    void addProduct(const Product& product);          // Adiciona um produto
    Product getProduct(const int& productId);         // Pega um produto
    
    void addClient(const Client& client);             // Adiciona um cliente
    Client getClient(const int& clientId);            // Pega um cliente
    
    void print();                                     // Imprime o grafo
};

