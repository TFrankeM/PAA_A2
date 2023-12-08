#include <iostream>
#include "../headers/structure.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

/* Modelo de Entrada (.txt):

num_vértices "número de vértices"
vértice "id" "x" "y"
aresta "id do vértice 1" "id do vértice 2"
produto "id" "preço" "peso"
vendedor "id" "id do vértice" "número de produtos" "id do produto 1" "id do produto 2" ...
entregador "id" "id do vértice" "capacidade"
CD "id" "id do vértice" "número de produtos" "id do produto 1" "quantidade do produto 1" "id do produto 2" "quantidade do produto 2" ...
cliente "id" "id do vértice"
ordem "id" "id do cliente" "tipo" "id do produto"

*/


// Função que lê uma linha do tipo "vértice" e adiciona o vértice ao grafo
void readVertex(GraphAdjList& g, istream& iss, int vertex_coords[][2])
{
    int id; int x; int y;
    iss >> id >> x >> y;

    vertex_coords[id][0] = x;
    vertex_coords[id][1] = y;
}


// Função que lê uma linha do tipo "aresta" e adiciona a aresta ao grafo
void readEdge(GraphAdjList& g, istream& iss, int vertex_coords[][2])
{
    int id1; int id2;
    iss >> id1 >> id2;

    // Calcula a distância entre os vértices
    float dist = sqrt(pow(vertex_coords[id1][0] - vertex_coords[id2][0], 2) + pow(vertex_coords[id1][1] - vertex_coords[id2][1], 2));
    g.addEdge(id1, id2, dist);
}


// Função que lê uma linha do tipo "produto" e adiciona o produto ao grafo
void readProduct(GraphAdjList& g, istream& iss)
{
    int id; double preco; double peso;
    iss >> id >> preco >> peso;
    Product p(id, preco, peso);
    g.addProduct(p);
}


// Função que lê uma linha do tipo "vendedor" e adiciona o vendedor ao grafo
void readSeller(GraphAdjList& g, istream& iss)
{
    int id; int vertex; int numProducts;
    iss >> id >> vertex >> numProducts;
    Seller s(id);

    // Adiciona os produtos ao vendedor
    for (int i = 0; i < numProducts; i++)
    {
        int idProduct;
        iss >> idProduct;
        s.addProduct(g.getProduct(idProduct));
    }

    g.getVertex(vertex).addSeller(s);
}


// Função que lê uma linha do tipo "entregador" e adiciona o entregador ao grafo
void readDeliveryPerson(GraphAdjList& g, istream& iss)
{
    int id; int vertex; double capacity;
    iss >> id >> vertex >> capacity;
    DeliveryPerson d(id, capacity);
    g.getVertex(0).addDeliveryPerson(d);
}


// Função que lê uma linha do tipo "CD" e adiciona o centro de distribuição ao grafo
void readDistributionCenter(GraphAdjList& g, istream& iss)
{
    int id; int vertex; int numProducts;
    iss >> id >> vertex >> numProducts;
    DistributionCenter dc(id);

    // Adiciona os produtos ao centro de distribuição
    for (int i = 0; i < numProducts; i++)
    {
        int idProduct; int quantity;
        iss >> idProduct >> quantity;
        dc.addProduct(g.getProduct(idProduct), quantity);
    }

    g.getVertex(0).addDistributionCenter(dc);
}


// Função que lê uma linha do tipo "cliente" e adiciona o cliente ao grafo
void readClient(GraphAdjList& g, istream& iss)
{
    int id; int vertex;
    iss >> id >> vertex;
    Client c(id);
    g.addClient(c);
    g.getVertex(0).addClient(c);
}


// Função que lê uma linha do tipo "ordem" e adiciona a ordem ao grafo
void readOrder(GraphAdjList& g, istream& iss)
{
    int id; int client; string s_orderType; int product;
    iss >> id >> client >> s_orderType >> product;

    // Converte o tipo de ordem para o enum correspondente   
    OrderType orderType;
    if (s_orderType == "Simple") orderType = OrderType::Simple;
    else if (s_orderType == "Optimized") orderType = OrderType::Optimized;
    
    Order o(id, g.getProduct(product), orderType);
    g.getClient(client).addOrder(o);
}


// Função que lê uma linha e chama a função correspondente
void readLine(GraphAdjList& g, string line, int vertex_coords[][2])
{
    // Separa a linha em palavras e pega a primeira (tipo)
    istringstream iss(line);
    string type;
    iss >> type;

    if (type == "vértice")
    {
        readVertex(g, iss, vertex_coords);
    } 
    else if (type == "aresta")
    {
        readEdge(g, iss, vertex_coords);
    }
    else if (type == "produto")
    {
        readProduct(g, iss);
    }
    else if (type == "vendedor")
    {
        readSeller(g, iss);
    }
    else if (type == "entregador")
    {
        readDeliveryPerson(g, iss);
    }
    else if (type == "CD")
    {
        readDistributionCenter(g, iss);
    }
    else if (type == "cliente")
    {
        readClient(g, iss);
    }
    else if (type == "ordem")
    {
        readOrder(g, iss);
    }
}


void readFile(GraphAdjList& g, string filename)
{
    // Abre o arquivo de entrada
    ifstream file;
    file.open(filename);

    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) throw runtime_error("Erro ao abrir o arquivo de entrada");

    string line;

    // Lê o número de vértices do arquivo
    getline(file, line);
    istringstream iss(line);
    int num_vertices;
    iss >> num_vertices;

    // Inicializa o grafo
    GraphAdjList g(num_vertices);

    // Inicializa a matriz de coordenadas dos vértices
    int vertex_coords[num_vertices][2];

    // Lê e processa cada linha do arquivo de entrada
    while (getline(file, line))
    {
        readLine(g, line, vertex_coords);
    }

    file.close();

    // Imprime o grafo resultante
    g.print();
}
