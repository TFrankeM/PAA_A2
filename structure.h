#include <iostream>
#include <vector>

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


/* Product Header*/
class Product 
{
private:
    string id;          // Identificador único para product
    double price;       // Preço do produto
    double weight;      // Peso do produto

public:
    // Construtor para initializar um objeto Product
    Product(const string& prodId, double prodPrice, double prodWeight);

    // Métodos de acesso para retornar atributos do produto
    string getId() const;         // Pega o product ID
    double getPrice() const;      // Pega o product preço
    double getWeight() const;     // Pega o product peso

    // Métodos de mudança para trocar atributos do produto
    void setPrice(double newPrice);             // Define um novo preço para o produto
    void setWeight(double newWeight);           // Define um novo peso para o produto
};


/* Seller Header*/
class Seller {
private:
    string id;                  // Identificador único para seller
    vector<Product> catalog;    // Uma lista de produtos que o vendedor oferece

public:
    // Construtor para initializar um objeto Seller
    Seller(const string& sellerId);

    // Métodos de acesso para retornar atributos seller ID
    string getId() const;

    // Métodos de mudança para trocar atributos do produto
    void addProduct(const Product& product);            // Adiciona novo produto
    void removeProduct(const string& productId);        // Remove produto
    Product getProduct(const string& productId) const;  // Pega produto
};