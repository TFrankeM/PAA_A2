#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "../headers/txt_reader.h"


using namespace std;

/* Modelo de Entrada (.txt):

#vértices "número de vértices"
#vendedores "número de vendedores"
#entregadores "número de entregadores"
#CDs "número de centros de distribuição"
#clientes "número de clientes"

vértice "id" "x" "y"
aresta "id do vértice 1" "id do vértice 2"
produto "id" "preço" "peso"
vendedor "id" "vértice1" "vértice2" "distancia do vértice1" "número de produtos" "id do produto 1" "id do produto 2" ...
entregador "id" "vértice1" "vértice2" "distancia do vértice1" "capacidade"
CD "id" "vértice1" "vértice2" "distancia do vértice1" "número de produtos" "id do produto 1" "quantidade do produto 1" "id do produto 2" "quantidade do produto 2" ...
cliente "id" "vértice1" "vértice2" "distancia do vértice1"
ordem "id" "id do cliente" "id do vendedor" "tipo" "id do produto" 

*/


// Função que lê uma linha do tipo "vértice" e adiciona o vértice ao grafo
void readVertex(stringstream& iss, float vertex_coords[][2])
{
    int id; float x; float y;
    iss >> id >> x >> y;

    // Normaliza o ID do vértice
    id--;

    vertex_coords[id][0] = x;
    vertex_coords[id][1] = y;
}


// Função que lê uma linha do tipo "aresta" e adiciona a aresta ao grafo
void readEdge(GraphAdjList& g, stringstream& iss, float vertex_coords[][2])
{
    int id1; int id2;
    iss >> id1 >> id2;

    // Normaliza os IDs dos vértices
    id1--; id2--;

    // Calcula a distância entre os vértices
    float dist = sqrt(pow(vertex_coords[id1][0] - vertex_coords[id2][0], 2) + pow(vertex_coords[id1][1] - vertex_coords[id2][1], 2));

    g.addEdge(id1, id2, dist);
    g.addEdge(id2, id1, dist);
}


// Função que lê uma linha do tipo "produto" e adiciona o produto ao grafo
void readProduct(GraphAdjList& g, stringstream& iss)
{
    int id; double preco; double peso;
    iss >> id >> preco >> peso;
    Product p(id, preco, peso);
    g.addProduct(p);
}


// Função que lê uma linha do tipo "vendedor" e adiciona o vendedor ao grafo
void readSeller(GraphAdjList& g, stringstream& iss)
{
    int id; int vertex1; int vertex2; float distance; int numProducts;
    iss >> id >> vertex1 >> vertex2 >> distance >> numProducts;

    // Normaliza os IDs dos vértices
    vertex1--; vertex2--;

    // Adiciona o vértice do vendedor
    Vertex adress = g.addVertex(vertex1, vertex2, distance);
    Seller s(id, adress.getId());

    // Adiciona os produtos ao vendedor
    for (int i = 0; i < numProducts; i++)
    {
        int idProduct;
        iss >> idProduct;
        s.addProduct(g.getProduct(idProduct));
    }

    adress.addSeller(s);
    g.addSeller(s);
}


// Função que lê uma linha do tipo "entregador" e adiciona o entregador ao grafo
void readDeliveryPerson(GraphAdjList& g, stringstream& iss)
{
    int id; int vertex1; int vertex2; float distance; int capacity;
    iss >> id >> vertex1 >> vertex2 >> distance >> capacity;
    DeliveryPerson d(id, capacity);

    // Normaliza os IDs dos vértices
    vertex1--; vertex2--;

    // Adiciona o vértice do entregador
    g.addVertex(vertex1, vertex2, distance);
    g.getVertex(g.getNumRealVertices()-1).addDeliveryPerson(d);
}


// Função que lê uma linha do tipo "CD" e adiciona o centro de distribuição ao grafo
void readDistributionCenter(GraphAdjList& g, stringstream& iss)
{
    int id; int vertex1; int vertex2; float distance; int numProducts;
    iss >> id >> vertex1 >> vertex2 >> distance >> numProducts;
    DistributionCenter dc(id);

    // Normaliza os IDs dos vértices
    vertex1--; vertex2--;

    // Adiciona os produtos ao centro de distribuição
    for (int i = 0; i < numProducts; i++)
    {
        int idProduct; int quantity;
        iss >> idProduct >> quantity;
        dc.addProduct(g.getProduct(idProduct), quantity);
    }

    // Adiciona o vértice do centro de distribuição
    g.addVertex(vertex1, vertex2, distance);
    g.getVertex(g.getNumRealVertices()-1).addDistributionCenter(dc);
}


// Função que lê uma linha do tipo "cliente" e adiciona o cliente ao grafo
void readClient(GraphAdjList& g, stringstream& iss)
{
    int id; int vertex1; int vertex2; float distance;
    iss >> id >> vertex1 >> vertex2 >> distance;

    // Normaliza os IDs dos vértices
    vertex1--; vertex2--;

    // Adiciona o vértice do cliente
    Vertex adress = g.addVertex(vertex1, vertex2, distance);
    Client c(id, adress.getId());
    adress.addClient(c);
    g.add_or_upClient(c);
}


// Função que lê uma linha do tipo "ordem" e adiciona a ordem ao grafo
void readOrder(GraphAdjList& g, stringstream& iss)
{
    int id; int client; int seller; string s_orderType; int product;
    iss >> id >> client >> seller >> s_orderType >> product;

    // Converte o tipo de ordem para o enum correspondente   
    OrderType orderType;
    if (s_orderType == "Simple") orderType = OrderType::Simple;
    else if (s_orderType == "Optimized") orderType = OrderType::Optimized;

    Client clientObj = g.getClient(client);
    Seller sellerObj = g.getSeller(seller);
    Order o(id, g.getProduct(product), orderType, sellerObj.getAddress(), clientObj.getAddress());
    
    clientObj.addOrder(o);
    g.add_or_upClient(clientObj);
}

// Função que lê uma linha e chama a função correspondente
void readLine(GraphAdjList& g, string line, float vertex_coords[][2])
{
    // Separa a linha em palavras e pega a primeira (tipo)
    stringstream iss(line);
    string type;
    iss >> type;

    if (type == "vértice")
    {
        readVertex(iss, vertex_coords);
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

GraphAdjList readFile(string filename)
{
    // Abre o arquivo de entrada
    ifstream file;
    file.open(filename);

    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) throw runtime_error("Erro ao abrir o arquivo de entrada");

    string line;

    // Lê o número de vértices do arquivo
    getline(file, line);
    int num_vertices = stoi(line.substr(line.find(" ")));

    // Lê o número de entidades do arquivo
    int num_entities = 0;
    while (getline(file, line))
    {
        if (line[0] != '#') break;
        num_entities += stoi(line.substr(line.find(" ")));
    }

    // Inicializa o grafo
    GraphAdjList g(num_vertices, num_entities);

    // Inicializa a matriz de coordenadas dos vértices
    float vertex_coords[num_vertices][2];

    // Lê e processa cada linha do arquivo de entrada
    while (getline(file, line))
    {
        readLine(g, line, vertex_coords);
    }

    file.close();

    return g;
}
