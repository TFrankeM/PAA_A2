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
EdgeNode::EdgeNode(Vertex m_otherVertex, EdgeNode* m_next, float m_length)
    : m_otherVertex(m_otherVertex)
    , m_next(m_next)
    , m_length(m_length)
{}

// Retorna o vértice de destino
Vertex EdgeNode::otherVertex() { return m_otherVertex; }

// Retorna o próximo nó
EdgeNode* EdgeNode::getNext() { return m_next; }

// Retorna o comprimento da aresta
float EdgeNode::getLength() { return m_length; }

// Atribui o próximo nó com tamanho length
void EdgeNode::setNext(EdgeNode* next) { m_next = next; }

// ==============================================


// Construtor da classe GraphAdjList
GraphAdjList::GraphAdjList(int numVertices)
    : m_numVertices(numVertices)
    , m_numEdges(0)
    , m_edges(nullptr)
    , m_products()
    , m_clients()
{
    m_edges = new EdgeNode*[numVertices]; // Aloca espaço em memória para a lista de adjacência
    for (int i = 0; i < numVertices; i++) m_edges[i] = nullptr; // Inicializa a lista de adjacência 
}

// Destrutor da classe GraphAdjList
GraphAdjList::~GraphAdjList()
{
    // Percorre todos os vértices do grafo
    for (int i = 1; i <= m_numVertices; i++)
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

// Retorna um vértice do grafo
Vertex GraphAdjList::getVertex(int id)
{
    // Verifica se o vértice existe
    if (id < 0 || id > m_numVertices) throw runtime_error("Vértice com ID " + to_string(id) + " não existe");

    // Retorna o vértice
    return Vertex(id);
}

// Retorna o número de vértices do grafo
int GraphAdjList::getNumVertices() { return m_numVertices; }


// Adiciona uma aresta ao grafo (v1 -> v2)
void GraphAdjList::addEdge(int id_v1, int id_v2, float length)
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

// Retorna o número de arestas do grafo
int GraphAdjList::getNumEdges() { return m_numEdges; }

// Retorna as arestas de um vértice
EdgeNode* GraphAdjList::getEdges(int id) { return m_edges[id]; }


// Adiciona um vértice no meio de uma aresta (v1 -> v2)
void GraphAdjList::addVertex(int id_v1, int id_v2, float distance)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[id_v1];
    while (edge != nullptr)
    {
        // Se a aresta já existe, quebra o loop
        if (edge->otherVertex().getId() == id_v2) break;
        edge = edge->getNext();
    }

    // Caso a aresta não exista, retorna
    if (edge == nullptr) return;

    // Caso a distância não seja menor que a distância da aresta, retorna
    if (distance >= edge->getLength()) return;

    // Adiciona o vértice no meio da aresta
    m_edges[id_v1] = new EdgeNode({m_numVertices}, m_edges[id_v1], distance);
    m_edges[m_numVertices] = new EdgeNode({id_v2}, m_edges[m_numVertices], distance);
    m_numVertices++;
    m_numEdges++;
}

// Adiciona um produto ao grafo
void GraphAdjList::addProduct(const Product& product)
{
    // Verifica se o produto já existe
    auto it = find_if(m_products.begin(), m_products.end(), [&product](const Product& p) { return p.getId() == product.getId(); });
    if (it != m_products.end()) throw runtime_error("Produto já existe");

    // Adiciona o produto ao grafo
    m_products.push_back(product);
}

// Pega um produto do grafo
Product GraphAdjList::getProduct(const int& productId)
{
    // Verifica se o produto existe
    auto it = find_if(m_products.begin(), m_products.end(), [&productId](const Product& p) { return p.getId() == productId; });
    if (it == m_products.end()) throw runtime_error("Produto não existe");

    // Retorna o produto
    return *it;
}

// Adiciona um cliente ao grafo
void GraphAdjList::addClient(const Client& client)
{
    // Verifica se o cliente já existe
    auto it = find_if(m_clients.begin(), m_clients.end(), [&client](const Client& c) { return c.getId() == client.getId(); });
    if (it != m_clients.end()) throw runtime_error("Cliente já existe");

    // Adiciona o cliente ao grafo
    m_clients.push_back(client);
}

// Pega um cliente do grafo
Client GraphAdjList::getClient(const int& clientId)
{
    // Verifica se o cliente existe
    auto it = find_if(m_clients.begin(), m_clients.end(), [&clientId](const Client& c) { return c.getId() == clientId; });
    if (it == m_clients.end()) throw runtime_error("Cliente com ID " + to_string(clientId) + " não existe");

    // Retorna o cliente
    return *it;
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

