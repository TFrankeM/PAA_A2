#include "../headers/structure.h"
#include <stdexcept>    // Para runtime_error
#include <algorithm>    // Para find_if e remove_if


// Construtor da classe Vertex
Vertex::Vertex(int id)
    : id(id),
    clients(),
    deliveryPeople(),
    distributionCenters(),
    sellers()
{}

// Retorna o id do vértice
int Vertex::getId() { return id; }

// Adiciona um cliente
void Vertex::addClient(const Client& client) { clients.push_back(client); }

// Adiciona um entregador
void Vertex::addDeliveryPerson(const DeliveryPerson& deliveryPerson) { deliveryPeople.push_back(deliveryPerson); }

// Adiciona um centro de distribuição
void Vertex::addDistributionCenter(const DistributionCenter& distributionCenter) { distributionCenters.push_back(distributionCenter); }

// Adiciona um vendedor
void Vertex::addSeller(const Seller& seller) { sellers.push_back(seller); }

// Retorna a lista de clientes
vector<Client> Vertex::getClients() { return clients; }

// Retorna a lista de entregadores
vector<DeliveryPerson> Vertex::getDeliveryPeople() { return deliveryPeople; }

// Retorna a lista de centros de distribuição
vector<DistributionCenter> Vertex::getDistributionCenters() { return distributionCenters; }

// Retorna a lista de vendedores
vector<Seller> Vertex::getSellers() { return sellers; }

// ==============================================


// Construtor da classe EdgeNode
EdgeNode::EdgeNode(Vertex m_otherVertex, EdgeNode* m_next, int m_length)
    : m_otherVertex(m_otherVertex)
    , m_next(m_next)
    , m_length(m_length)
{}

// Retorna o vértice de destino
Vertex EdgeNode::otherVertex() { return m_otherVertex; }

// Retorna o próximo nó
EdgeNode* EdgeNode::getNext() { return m_next; }

// Retorna o comprimento da aresta
int EdgeNode::getLength() { return m_length; }

// Atribui o próximo nó com tamanho length
void EdgeNode::setNext(EdgeNode* next) { m_next = next; }

// ==============================================


// Construtor da classe GraphAdjList
GraphAdjList::GraphAdjList(int numVertices)
    : m_numVertices(numVertices)
    , m_numEdges(0)
    , m_edges(nullptr)
{
    m_edges = new EdgeNode*[numVertices]; // Aloca espaço em memória para a lista de adjacência
    for (int i = 0; i < numVertices; i++) m_edges[i] = nullptr; // Inicializa a lista de adjacência 
}

// Destrutor da classe GraphAdjList
GraphAdjList::~GraphAdjList()
{
    // Percorre todos os vértices do grafo
    for (int i = 0; i < m_numVertices; i++)
    {
        EdgeNode* edge = m_edges[i];

        // Deleta todos os nós da lista de adjacência
        while (edge != nullptr)
        {
            EdgeNode* next = edge->getNext();
            delete edge;
            edge = next;
        }
    }

    // Deleta o vetor de vértices
    delete[] m_edges;
}

// Adiciona uma aresta ao grafo (v1 -> v2)
void GraphAdjList::addEdge(int id_v1, int id_v2, int length)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[id_v1];
    while (edge != nullptr)
    {
        // Se a aresta já existe, retorna
        if (edge->otherVertex().getId() == id_v2) return;
        edge = edge->getNext();
    }
    
    // Adiciona a aresta ao grafo
    m_edges[id_v1] = new EdgeNode({id_v2}, m_edges[id_v1], length);
    m_numEdges++;
}

// Remove uma aresta do grafo (v1 -> v2)
void GraphAdjList::removeEdge(int id_v1, int id_v2)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[id_v1];
    EdgeNode* prev = nullptr;
    while (edge != nullptr)
    {
        // Se a aresta existe, remove
        if (edge->otherVertex().getId() == id_v2)
        {
            if (prev == nullptr) m_edges[id_v1] = edge->getNext();
            else prev->setNext(edge->getNext());
            delete edge;
            m_numEdges--;
            return;
        }
        prev = edge;
        edge = edge->getNext();
    }
}

// Imprime o grafo
void GraphAdjList::print()
{
    // Percorre todos os vértices do grafo
    for (int i = 0; i < m_numVertices; i++)
    {
        for (EdgeNode* edge = m_edges[i]; edge != nullptr; edge = edge->getNext())
        {
            // Imprime a aresta (i -> edge->otherVertex())
            cout << i << " -> " << edge->otherVertex().getId() << " (" << edge->getLength() << ") ";
        }
        cout << endl;
    }
}

