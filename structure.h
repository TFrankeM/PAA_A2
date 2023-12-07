#include <iostream>

using namespace std;

// Cria o tipo "vertex" que é um inteiro
typedef int vertex;

/* EdgeNode Header*/
class EdgeNode
{
private:
    vertex m_otherVertex;
    EdgeNode* m_next;
    int m_length;

public:
    EdgeNode(vertex m_otherVertex, EdgeNode* m_next, int m_length); // Construtor
    vertex otherVertex(); // Retorna o vértice de destino
    EdgeNode* getNext(); // Retorna o próximo nó
    int getLength(); // Retorna o comprimento da aresta
    void setNext(EdgeNode* next); // Atribui o próximo nó
};

/* GraphAdjList Header*/
class GraphAdjList
{
private:
    int m_numVertices;
    int m_numEdges;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices); // Construtor
    ~GraphAdjList(); // Destrutor
    void addEdge(vertex v1, vertex v2, int length); // Adiciona uma aresta
    void removeEdge(vertex v1, vertex v2); // Remove uma aresta
    void print(); // Imprime o grafo
};

