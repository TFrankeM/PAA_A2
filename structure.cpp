#include "structure.h"
#include <algorithm> // Para find_if e remove_if

// Construtor da classe EdgeNode
EdgeNode::EdgeNode(vertex m_otherVertex, EdgeNode* m_next, int m_length)
    : m_otherVertex(m_otherVertex)
    , m_next(m_next)
    , m_length(m_length)
{}

// Retorna o vértice de destino
vertex EdgeNode::otherVertex() { return m_otherVertex; }

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
    for (vertex i = 0; i < numVertices; i++) m_edges[i] = nullptr; // Inicializa a lista de adjacência 
}

// Destrutor da classe GraphAdjList
GraphAdjList::~GraphAdjList()
{
    // Percorre todos os vértices do grafo
    for (vertex i = 0; i < m_numVertices; i++)
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
void GraphAdjList::addEdge(vertex v1, vertex v2, int length)
{
    // Percorre todos os nós da lista de adjacência
    EdgeNode* edge = m_edges[v1];
    while (edge != nullptr)
    {
        // Se a aresta já existe, retorna
        if (edge->otherVertex() == v2) return;
        edge = edge->getNext();
    }
    
    // Adiciona a aresta ao grafo
    m_edges[v1] = new EdgeNode(v2, m_edges[v1], length);
    m_numEdges++;
}

// Remove uma aresta do grafo (v1 -> v2)
void GraphAdjList::removeEdge(vertex v1, vertex v2)
{
    EdgeNode* edge = m_edges[v1];
    EdgeNode* prev = nullptr;

    // Percorre todos os nós da lista de adjacência
    while (edge != nullptr)
    {
        // Se a aresta foi encontrada, remove-a
        if (edge->otherVertex() == v2)
        {
            // Atualiza o ponteiro do nó anterior
            if (prev == nullptr) m_edges[v1] = edge->getNext();
            else prev->setNext(edge->getNext());

            // Deleta o nó
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
    for (vertex i = 0; i < m_numVertices; i++)
    {
        for (EdgeNode* edge = m_edges[i]; edge != nullptr; edge = edge->getNext())
        {
            // Imprime a aresta (i -> edge->otherVertex())
            cout << i << " -> " << edge->otherVertex() << " (" << edge->getLength() << ") ";
        }
        cout << endl;
    }
}

// ==============================================


// Constructor da classe produto
Product::Product(const string& prodId, double prodPrice, double prodWeight)
    : id(prodId)
    , price(prodPrice)
    , weight(prodWeight) 
{}

// retorna o produto ID
std::string Product::getId() const { return id; }

// Retorna o preço do produto
double Product::getPrice() const { return price; }

// Retorna o peso do produto
double Product::getWeight() const { return weight; }

// Atribui o preço do produto
void Product::setPrice(double newPrice) { price = newPrice; }

// Atribui o peso do produto
void Product::setWeight(double newWeight) { weight = newWeight; }

// ==============================================

// Construtor da classe vendedor
Seller::Seller(const string& sellerId)
    : id(sellerId)
{}

// Retorna o ID do vendedor
string Seller::getId() const { return id; }

// Adiciona novo produto ao catálogo do vendedor
void Seller::addProduct(const Product& product) {
    catalog.push_back(product);
}

// Remove um produto do catálogo do vendedor pelo seu ID
void Seller::removeProduct(const string& productId) {
    // O algoritmo remove_if reorganiza os elementos no intervalo [begin, end)
    // e retorna um iterador para o novo final desse intervalo.
    // Aqui, ele remove o produto cujo ID corresponde ao productId especificado.
    catalog.erase(remove_if(catalog.begin(), catalog.end(),
                                [&productId](const Product& product) {
                                    return product.getId() == productId;
                                }),
                            catalog.end());
}

// Recupera um produto do catálogo do vendedor pelo seu ID
Product Seller::getProduct(const string& productId) const {
    // O algoritmo find_if procura por um elemento para o qual o fornecido
    // predicado retorna verdadeiro e retorna um iterador para ele.
    // Aqui, procura um produto com o productId especificado.
    // A função lambda verifica se o ID do produto corresponde ao productId especificado.
    auto it = find_if(catalog.begin(), catalog.end(),
                                [&productId](const Product& product) {
                                    return product.getId() == productId;
                                });
    if (it != catalog.end()) {
        return *it;
    }
    throw runtime_error("Product not found");
}
