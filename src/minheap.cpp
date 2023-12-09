#include "../headers/minheap.h"
#include <algorithm>            // Para swap


// Construtor
MinHeap::MinHeap() 
    : size(0) 
{}

void MinHeap::heapify(int index) 
{
    int smallest = index;   // Índice atual
    
    // Calcula o índice dos nós filhos da esquerda e direita
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Se o nó filho da esquerda estiver no heap e for menor que o nó atual
    if (left < size && heap[left].first < heap[smallest].first) {
        smallest = left;        // Redefinimos o nó atual
    }

    // Se o nó filho da direita estiver no heap e for menor que o nó atual
    if (right < size && heap[right].first < heap[smallest].first) {
        smallest = right;       // Redefinimos o nó atual
    }

    // Se o menor nó não é o nó de ínicio, trocamos o nó de início com o menor 
    // nó e executamos heapify recursivamente na subárvore
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapify(smallest);
    }
}

// Adiciona novo elemento ao heap
void MinHeap::push(pair<int, Vertex> element) 
{
    heap.push_back(element);            // Adiciona elemento ao final do vetor
    int current = size++;               // Incrementa o tamanho
    int parent = (current - 1) / 2;     // Índice do nó pai

    // Enquanto o nó atual não for a cabeça e for menor do que o respectivo pai
    while (current > 0 && heap[current].first < heap[parent].first) {
        swap(heap[current], heap[parent]);             // Trocamos o nó filho pelo pai
        current = parent;                              // Repetimos iterativamente de baixo para cima no heap
        parent = (parent - 1) / 2;
    }
}

// Remove o primeiro elemento do heap (o de menor distância)
void MinHeap::pop() 
{
    if (size == 0) return;      // Heap já vazio
    heap[0] = heap[--size];     // Primeira posição recebe último elemento
    heap.pop_back();            // Remove o último elemento
    heapify(0);                 // Reordena o heap
}

// Retorna o primeiro elemento do heap (o de menor distância)
pair<int, Vertex> MinHeap::top() const 
{
    return heap[0];
}

// Retorna falso se o heap está vazio e verdadeiro caso contrário
bool MinHeap::empty() const 
{
    return size == 0;
}

