#include "../headers/structure.h"
#include <stdexcept>    // Para runtime_error
#include <algorithm>    // Para find_if e remove_if


// Construtor da classe Vertex
Vertex::Vertex(int id)
    : id(id)
    , client(nullptr)
    , deliveryPerson(nullptr)
    , distributionCenter(nullptr)
    , seller(nullptr)
{}

// Retorna o id do vértice
int Vertex::getId() { return id; }

// Adiciona um cliente
void Vertex::addClient(const Client& client) { this->client = new Client(client); }

// Adiciona um entregador
void Vertex::addDeliveryPerson(const DeliveryPerson& deliveryPerson) { this->deliveryPerson = new DeliveryPerson(deliveryPerson); }

// Adiciona um centro de distribuição
void Vertex::addDistributionCenter(const DistributionCenter& distributionCenter) { this->distributionCenter = new DistributionCenter(distributionCenter); }

// Adiciona um vendedor
void Vertex::addSeller(const Seller& seller) { this->seller = new Seller(seller); }

// Retorna o cliente
Client* Vertex::getClient() { return client; }

// Retorna o entregador
DeliveryPerson* Vertex::getDeliveryPerson() { return deliveryPerson; }

// Retorna o centro de distribuição
DistributionCenter* Vertex::getDistributionCenter() { return distributionCenter; }

// Retorna o vendedor
Seller* Vertex::getSeller() { return seller; }

// ==============================================


// Construtor da classe EdgeNode
EdgeNode::EdgeNode(Vertex* m_otherVertex, EdgeNode* m_next, float m_length)
    : m_otherVertex(m_otherVertex)
    , m_next(m_next)
    , m_length(m_length)
{}

// Retorna o vértice de destino
Vertex* EdgeNode::otherVertex() { return m_otherVertex; }

// Retorna o próximo nó
EdgeNode* EdgeNode::getNext() { return m_next; }

// Retorna o comprimento da aresta
float EdgeNode::getLength() { return m_length; }

// Atribui o próximo nó com tamanho length
void EdgeNode::setNext(EdgeNode* next) { m_next = next; }

// ==============================================


// Construtor da classe GraphAdjList
GraphAdjList::GraphAdjList(int numRealVertices, int numEntities)
    : m_numVertices(numRealVertices + numEntities)
    , m_numRealVertices(numRealVertices)
    , m_numEdges(0)
    , m_edges(nullptr)
    , m_products()
    , m_clients()
{
    m_edges = new EdgeNode*[m_numVertices]; // Aloca espaço em memória para a lista de adjacência
    for (int i = 0; i < m_numVertices; i++) m_edges[i] = nullptr; // Inicializa a lista de adjacência 
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

// Retorna um vértice do grafo
Vertex* GraphAdjList::getVertex(int id)
{
    // Verifica se o vértice existe
    if (id < 0 || id >= m_numVertices) throw runtime_error("Vértice com ID " + to_string(id) + " não existe");

    // Retorna o vértice
    for (int i = 0; i < m_numVertices; i++)
    {
        for (EdgeNode* edge = m_edges[i]; edge != nullptr; edge = edge->getNext())
        {
            if (edge->otherVertex()->getId() == id) return (edge->otherVertex());
        }
    }

    throw runtime_error("Vértice com ID " + to_string(id) + " não existe");
}

// Retorna o número de vértices do grafo
int GraphAdjList::getNumVertices() { return m_numVertices; }

// Retorna o número de vértices reais do grafo
int GraphAdjList::getNumRealVertices() { return m_numRealVertices; }


// Adiciona uma aresta ao grafo (v1 -> v2)
void GraphAdjList::addEdge(int id_v1, int id_v2, float length)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[id_v1];
    while (edge != nullptr)
    {
        // Se a aresta já existe, retorna
        if (edge->otherVertex()->getId() == id_v2) return;
        edge = edge->getNext();
    }
    
    // Adiciona a aresta ao grafo
    Vertex* new_vertex = new Vertex(id_v2);
    m_edges[id_v1] = new EdgeNode(new_vertex, m_edges[id_v1], length);
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
        if (edge->otherVertex()->getId() == id_v2)
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



// Adiciona um vértice no meio de uma aresta (v1 -> v2) e retorna o vértice adicionado
Vertex* GraphAdjList::addVertex(int id_v1, int id_v2, float distance)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[id_v1];
    while (edge != nullptr)
    {
        // Se a aresta já existe, quebra o loop
        if (edge->otherVertex()->getId() == id_v2) break;
        edge = edge->getNext();
    }

    // Caso a aresta não exista, retorna
    if (edge == nullptr)
    {
        cout << "Aresta " << id_v1 << " -> " << id_v2 << " não existe" << endl;
        return nullptr;
    }

    float length = edge->getLength();
    
    // Caso a distância não seja menor que a distância da aresta, retorna
    if (distance > length)
    { 
        cout << "Distância: " << distance << " | Comprimento da aresta: " << length << endl; // "Distância maior que a distância da aresta
        cout << "Vértice 1: " << id_v1 << " | Vértice 2: " << id_v2 << endl;
        throw runtime_error("Distância maior que a distância da aresta"); 
    }

    // Adiciona o vértice no meio da aresta
    addEdge(id_v1, m_numRealVertices , distance);
    addEdge(m_numRealVertices, id_v2, length - distance);
    
    addEdge(m_numRealVertices, id_v1, distance);
    addEdge(id_v2, m_numRealVertices++, length - distance);
    // Retorna o vértice adicionado
    for (EdgeNode* edges = m_edges[id_v1]; edges != nullptr; edges = edges->getNext())
    {
        if (edges->otherVertex()->getId() == m_numRealVertices - 1) return edges->otherVertex();
    }

    return nullptr;
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

// Adiciona ou atualiza um cliente do grafo
void GraphAdjList::add_or_upClient(const Client& client)
{
    // Verifica se o cliente já existe
    auto it = find_if(m_clients.begin(), m_clients.end(), [&client](const Client& c) { return c.getId() == client.getId(); });
    
    // Se o cliente já existe, atualiza
    if (it != m_clients.end()) *it = client;

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

// Adiciona um vendendor ao grafo
void GraphAdjList::addSeller(const Seller& seller)
{
    // Verifica se o vendedor já existe
    auto it = find_if(m_sellers.begin(), m_sellers.end(), [&seller](const Seller& s) { return s.getId() == seller.getId(); });
    if (it != m_sellers.end()) throw runtime_error("Vendedor já existe");

    // Adiciona o vendedor ao grafo
    m_sellers.push_back(seller);
}

// Pega um vendedor do grafo
Seller GraphAdjList::getSeller(const int& sellerId)
{
    // Verifica se o vendedor existe
    auto it = find_if(m_sellers.begin(), m_sellers.end(), [&sellerId](const Seller& s) { return s.getId() == sellerId; });
    if (it == m_sellers.end()) throw runtime_error("Vendedor com ID " + to_string(sellerId) + " não existe");

    // Retorna o vendedor
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
            cout << i + 1 << " -> " << edge->otherVertex()->getId() + 1 << " (" << edge->getLength() << ") ";
        }
        cout << endl;
    }
}

