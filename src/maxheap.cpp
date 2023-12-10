#include "../headers/maxheap.h"
#include <algorithm>

// Construtor que inicializa o heap com tamanho 0
MaxHeap::MaxHeap() 
    : size(0)
{}

// Função Heapify para manter a propriedade max-heap
void MaxHeap::heapify(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Compare e encontre o maior entre o nó e seus filhos
    if (left < size && heap[left].totalDistance > heap[largest].totalDistance) {
        largest = left;
    }
    if (right < size && heap[right].totalDistance > heap[largest].totalDistance) {
        largest = right;
    }

    // Se o maior não for o nó atual, troque e continue heapificando
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapify(largest);
    }
}

// Insere um elemento para o heap
void MaxHeap::push(Path element) {
    heap.push_back(element);            // Adiciona o elemeno no fim do heap
    int current = size++;
    int parent = (current - 1) / 2;

    //Ajuste a posição do elemento recém-adicionado para manter a propriedade max-heap
    while (current > 0 && heap[current].totalDistance > heap[parent].totalDistance) {
        std::swap(heap[current], heap[parent]);
        current = parent;
        parent = (parent - 1) / 2;
    }
}

//Retira o elemento superior (o maior) do heap
void MaxHeap::pop() {
    if (size == 0) return;      // Checa se o heap está vazio
    heap[0] = heap[--size];     // Troca a raiz pelo último elemento do monte
    heap.pop_back();            // Remove o último elemento
    heapify(0);                 // Heapify a partir da raiz
}

// Obtém o elemento superior do heap
Path MaxHeap::top() const {
    return heap[0];
}

//Verifica se o heap está vazio
bool MaxHeap::empty() const {
    return size == 0;
}

// Obtém o tamanho do heap
int MaxHeap::getSize() const {
    return size;
}

