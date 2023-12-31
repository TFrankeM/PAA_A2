#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <utility> // Para 'pair'
#include "structure.h"

using namespace std;

// Classe MinHeap para lidar com estruturas de dados de heap mínimo
class MinHeap 
{
private:
    vector<pair<int, Vertex*>> heap;    // O heap é um vetor de pares <distance, vertex ID>
    int size;                       // Tamanho do heap

    void heapify(int index);        // Método para manter a propriedade de heap

public:
    // Construtor
    MinHeap();

    void push(pair<int, Vertex*> element);  // Adiciona novo elemento ao heap
    void pop();                         // Remove o elemento do topo do heap
    pair<int, Vertex*> top() const;         // Retorna o elemento do topo do heap
    bool empty() const;                 // Checa se o heap está vazio
};

#endif

