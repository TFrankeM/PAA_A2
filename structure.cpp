#include "structure.h"


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
