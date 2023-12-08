#include "../headers/operations.h"
#include "../headers/minheap.h"     // Incluir classe MinHeap
#include <vector>
#include <limits>
#include <algorithm>  // Para swap
#include <utility>    // Para pair


/*
        OPERAÇÃO 1: encontrar entregadores próximos.

    - Quando um pedido for postado será necessário encontrar um entregador para fazer o transporte.
    - Deve-se buscar os n entregadores mais próximos do local de coleta
        - Ou seja, os entregadores cujas rotas para o endereço do vendedor tenham o menor tamanho.
    - A entrada da operação deverá ser o pedido, e o resultado a lista de entregadores sugeridos.
*/

vector<pair<int, int>> GraphOperations::findNearestDeliveryPeople(GraphAdjList& graph, 
                                                                  int startVertexId, 
                                                                  int numDeliveryPeople) 
{
    // Obtém número |V| de vértices do grafo
    int m_numVertices = graph.getNumVertices();

    // Lista "distancia" de tamanho |V| com valores infinito
    vector<int> distances(m_numVertices, numeric_limits<int>::max());

    // Lista "visitado" de tamanho |V| com valores falso
    vector<bool> visited(m_numVertices, false);

    // Cria uma fila de prioridade heap, ordenando da menor para a maior distância
    MinHeap heap;

    // Define distância do vértice inicial como zero
    distances[startVertexId] = 0;
    // Coloca o vértice inicial com a sua distância até a origem no topo do heap
    heap.push({distances[startVertexId], startVertexId});

    // Cria uma lista para os entregadores selecionado: <distância até o vértice de origem, ID do entregador>
    vector<pair<int, int>> deliveryPeopleFound;
    // Número de entregadores selecionados
    int peopleFound = 0;

    // Enquanto o heap não está vazio e o número de entregadores selecionados é menor do que o exigido, fazemos:
    while (!heap.empty() && peopleFound < numDeliveryPeople) {
        // Removemos o vértice com a menor distância do heap
        int currentVertexId = heap.top().second;
        heap.pop();

        // Se o vértice atual já foi visitado, ignoramos ele
        if (visited[currentVertexId]) {
            continue;
        }
        // Define o vértice atual como visitado
        visited[currentVertexId] = true;

        // Se a distância do vértice atual é máxima, já visitamos todos os vértices possíveis
        if (distances[currentVertexId]  == numeric_limits<int>::max()) {
            break;
        }

        // Lista de entregadores no vértice atual
        vector<DeliveryPerson> deliveryPeople = graph.getVertex(currentVertexId).getDeliveryPeople();

        // Percorremos a lista deliveryPeople adicionando o entregador a lista de entregadores selecionados 
        // se o número de entregadores procurado não tiver sido atingido
        if (!deliveryPeople.empty())
        {
            // 'deliveryPerson' é o atual elemento de 'deliveryPeople'
            for (const DeliveryPerson& deliveryPerson : deliveryPeople) 
            {
                // Adiciona <ID do entregador, distância> à lista de selecionados se ela não estiver cheia
                if (peopleFound < numDeliveryPeople) 
                {
                    deliveryPeopleFound.push_back({deliveryPerson.getId(), distances[currentVertexId]});
                    peopleFound++;
                } 
                else 
                {
                    break; // Sai do loop se foram encontradas pessoas suficientes
                }
            }
        }
        
        // Iterate pelas arestas do vértice atual
        for (EdgeNode* edge = graph.getEdges(currentVertexId); edge != nullptr; edge = edge->getNext())
        {
            // Pega o índice do vértice vizinho
            int neighborVertexId = edge->otherVertex().getId();

            // Se o vizinho não foi visitado ainda
            if(!visited[neighborVertexId])
            {
                // Acessamos o comprimento da aresta
                int edgeLength = edge->getLength();

                // Se a distância de v1 + comprimento da rua < v2 atual
                if (distances[currentVertexId] + edgeLength < distances[neighborVertexId]) 
                {
                    // Atualizamos v2 = distância de v1 + comprimento da rua
                    distances[neighborVertexId] = distances[currentVertexId] + edgeLength;
                    // Adicionamos o novo vértice à lista
                    heap.push({distances[neighborVertexId], neighborVertexId});
                }
            }
        }
    }

    return deliveryPeopleFound;
}

/*
        OPERAÇÃO 2: definir a rota de uma entrega simples.
    - Caso o pedido seja simples, após receber a confirmação de um entregador precisamos encontrar 
    a rota com a menor distância total para entrega.
    - Essa rota deverá iniciar na posição corrente do entregador, considerar a coleta do produto no 
    endereço do vendedor, e terminar no endereço do cliente.
    - A entrada da operação deverá ser o pedido e o entregador escolhido, e o resultado a lista de 
    segmentos representando a rota.
*/


/*
        OPERAÇÃO 3: definir a rota de uma entrega considerando centros de distribuição.
    - Caso o pedido seja otimizado, um entregador deverá coletar o produto em algum centro de distribuição, 
    e transportá-lo para o endereço do cliente.
    - A operação consiste em buscar os n entregadores cujas rotas apresentem a menor distância total, 
    considerando a passagem por algum centro de distribuição que contenha o produto no seu inventário.
    - A entrada da operação deverá ser o pedido, e o resultado uma lista contendo em cada elemento: o 
    entregador, o centro de distribuição, e a lista de segmentos representando a rota.
*/


/*
        OPERAÇÃO 4: sugerir entregas adicionais com base em uma rota.
    - Buscando aproveitar o deslocamento de um entregador em uma rota, proponha uma solução para sugerir 
    pedidos adicionais buscando maximizar o faturamento.
    - Essa solução deverá considerar:
        - A capacidade de transporte do tipo do veículo.
        - O peso e o preço de cada produto.
        - A sua disponibilidade no inventário.
*/

