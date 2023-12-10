#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <algorithm>

// Estrutura para armazenar 
struct Path 
{
    int deliveryPersonId;           // ID do entregador
    int distributionCenterId;       // Central de distribuição
    std::vector<int> route;         // Lista com as arestas (rota)
    int totalDistance;              // Distância total até a origem

    // A função operator< define como dois objetos Path são comparados
    bool operator<(const Path& other) const {
        return totalDistance < other.totalDistance;
    }
};

// Classe MaxHeap para lidar com estruturas de dados de heap máximo
class MaxHeap {
private:
    std::vector<Path> heap;         // O heap é um vetor de pares <distance, vertex ID>
    int size;
    
    void heapify(int index);        // Método para manter a propriedade de heap

public:
    // Construtor
    MaxHeap();

    void push(Path element);        // Adiciona novo elemento ao heap
    void pop();                     // Remove o elemento do topo do heap
    Path top() const;               // Retorna o elemento do topo do heap
    bool empty() const;             // Checa se o heap está vazio
    int getSize() const;            // Obtém o tamanho do heap
};

#endif
