#include "../headers/operations.h"
#include <vector>
#include <limits>
#include <algorithm>  // Para swap
#include <utility>    // Para pair
#include <map>

/*
        OPERAÇÃO 1: encontrar entregadores próximos.

    - Quando um pedido for postado será necessário encontrar um entregador para fazer o transporte.
    - Deve-se buscar os n entregadores mais próximos do local de coleta
        - Ou seja, os entregadores cujas rotas para o endereço do vendedor tenham o menor tamanho.
    - A entrada da operação deverá ser o pedido, e o resultado a lista de entregadores sugeridos.
*/

vector<pair<DeliveryPerson, float>> GraphOperations::findNearestDeliveryPeople(GraphAdjList& graph, 
                                                                  Order order, 
                                                                  int numDeliveryPeople) 
{
    // Obtém vértice de origem
    Vertex* startVertex = graph.getVertex(order.getSellerAddress());

    // Obtém número |V| de vértices do grafo
    int m_numVertices = graph.getNumVertices();

    // Lista "distancia" de tamanho |V| com valores infinito
    vector<float> distances(m_numVertices, numeric_limits<float>::max());

    // Lista "visitado" de tamanho |V| com valores falso
    vector<bool> visited(m_numVertices, false);

    // Cria uma fila de prioridade heap, ordenando da menor para a maior distância
    MinHeap heap;

    // Define distância do vértice inicial como zero
    distances[startVertex->getId()] = 0;
    // Coloca o vértice inicial com a sua distância até a origem no topo do heap
    heap.push({distances[startVertex->getId()], startVertex});

    // Cria uma lista para os entregadores selecionado: <distância até o vértice de origem, ID do entregador>
    vector<pair<DeliveryPerson, float>> deliveryPeopleFound;
    // Número de entregadores selecionados
    int peopleFound = 0;

    // Enquanto o heap não está vazio e o número de entregadores selecionados é menor do que o exigido, fazemos:
    while (!heap.empty() && peopleFound < numDeliveryPeople) {
        // Removemos o vértice com a menor distância do heap
        Vertex* currentVertex = heap.top().second;
        heap.pop();

        // Se o vértice atual já foi visitado, ignoramos ele
        if (visited[currentVertex->getId()]) {
            continue;
        }
        // Define o vértice atual como visitado
        visited[currentVertex->getId()] = true;

        // Se a distância do vértice atual é máxima, já visitamos todos os vértices possíveis
        if (distances[currentVertex->getId()]  == numeric_limits<float>::max()) {
            break;
        }

        // Lista de entregadores no vértice atual
        DeliveryPerson* deliveryPerson = currentVertex->getDeliveryPerson();

        // Percorremos a lista deliveryPeople adicionando o entregador a lista de entregadores selecionados 
        // se o número de entregadores procurado não tiver sido atingido
        if (deliveryPerson)
        {
            // Adiciona <Entregador, distância> à lista de selecionados se ela não estiver cheia
            if (peopleFound < numDeliveryPeople) 
            {
                deliveryPeopleFound.push_back({*deliveryPerson, distances[currentVertex->getId()]});
                peopleFound++;
            } 
            else 
            {
                break; // Sai do loop se foram encontradas pessoas suficientes
            }
        }
        
        // Iterate pelas arestas do vértice atual
        for (EdgeNode* edge = graph.getEdges(currentVertex->getId()); edge != nullptr; edge = edge->getNext())
        {
            // Pega o índice do vértice vizinho
            Vertex* neighborVertex = edge->otherVertex();

            // Se o vizinho não foi visitado ainda
            if(!visited[neighborVertex->getId()])
            {
                // Acessamos o comprimento da aresta
                float edgeLength = edge->getLength();

                // Se a distância de v1 + comprimento da rua < v2 atual
                if (distances[currentVertex->getId()] + edgeLength < distances[neighborVertex->getId()]) 
                {
                    // Atualizamos v2 = distância de v1 + comprimento da rua
                    distances[neighborVertex->getId()] = distances[currentVertex->getId()] + edgeLength;
                    // Adicionamos o novo vértice à lista
                    heap.push({distances[neighborVertex->getId()], neighborVertex});
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


vector<EdgeNode*> GraphOperations::defineSimpleDeliveryRoute(GraphAdjList& graph,
                                                             Order order, 
                                                             DeliveryPerson deliveryPerson) 
{
    Vertex* sellerVertex = graph.getVertex(order.getSellerAddress());
    Vertex* clientVertex = graph.getVertex(order.getClientAddress());
    
    // A lista para armazenar a rota final
    vector<EdgeNode*> route;

    // Primeiro, encontrar o caminho do entregador até o vendedor
    vector<Vertex*> pathToSeller = findPath(graph, graph.getVertex(deliveryPerson.getAddress()), sellerVertex);

    // Adiciona este caminho à rota
    addToRoute(graph, route, pathToSeller);

    // Depois, encontrar o caminho do vendedor até o cliente
    vector<Vertex*> pathToClient = findPath(graph, sellerVertex, clientVertex);
    
    // Adiciona este caminho à rota
    addToRoute(graph, route, pathToClient);

    // Retorna a rota completa
    return route;
}

// Dijkstra para encontrar o menor caminho
vector<Vertex*> GraphOperations::findPath(GraphAdjList& graph, Vertex* startVertex, Vertex* endVertex) {
    MinHeap heap;
    vector<float> distances(graph.getNumVertices(), numeric_limits<int>::max());
    vector<bool> visited(graph.getNumVertices(), false);
    vector<Vertex*> parents(graph.getNumVertices(), nullptr);

    distances[startVertex->getId()] = 0;
    parents[startVertex->getId()] = startVertex;
    heap.push({distances[startVertex->getId()], startVertex});

    while (!heap.empty()) {        
        Vertex* currentVertex = heap.top().second; // Vertice com valor minimo
        cout << "currentVertex: " << currentVertex->getId() << endl;
        heap.pop(); // Remove Verice do Heap

        if (distances[currentVertex->getId()] == numeric_limits<float>::max()) { break; }

        if (visited[currentVertex->getId()]) continue;
        visited[currentVertex->getId()] = true;

        if (currentVertex->getId() == endVertex->getId()) break;
        EdgeNode* edge = graph.getEdges(currentVertex->getId());

        while(edge){
            Vertex* neighborVertex = edge->otherVertex();
            if (!visited[neighborVertex->getId()]) {
                float edgeLength = edge->getLength();

                if(distances[currentVertex->getId()] + edgeLength < distances[neighborVertex->getId()]){
                    parents[neighborVertex->getId()] = currentVertex;
                    distances[neighborVertex->getId()] = distances[currentVertex->getId()] + edgeLength;
                    heap.push({distances[neighborVertex->getId()], neighborVertex});
                }
                
            }

            edge = edge->getNext();
        
        }
        visited[currentVertex->getId()] = true;
    }

    // Reconstruir o caminho do destino de volta à origem
    vector<Vertex*> path;
    for (Vertex* v = endVertex; v->getId() != startVertex->getId(); v = parents[v->getId()]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); // O caminho está na ordem inversa
    return path;
}


// Define a função que adiciona arestas ao vetor de rota com base em uma sequencia de vertices
void GraphOperations::addToRoute(GraphAdjList& graph, vector<EdgeNode*>& route, vector<Vertex*> path) {
    // Itera sobre cada vértice no caminho, exceto o último
    for (size_t i = 0; i < path.size() - 1; ++i) {
        // Vértice atual no caminho
        Vertex* from = path[i];
        // Próximo vértice no caminho
        Vertex* to = path[i + 1];
        
        // Itera sobre as arestas que saem do vértice from
        for (EdgeNode* edge = graph.getEdges(from->getId()); edge != nullptr; edge = edge->getNext()) {
            // Verifica se a aresta conecta ao vértice to
            if (edge->otherVertex()->getId() == to->getId()) {
                // Se sim, adiciona a aresta ao vetor route
                route.push_back(edge);
                // Sai do loop interno, pois a aresta correta foi encontrada
                break;
            }
        }
    }
}


/*
        OPERAÇÃO 3: definir a rota de uma entrega considerando centros de distribuição.
    - Caso o pedido seja otimizado, um entregador deverá coletar o produto em algum centro de distribuição, 
    e transportá-lo para o endereço do cliente.
    - A operação consiste em buscar os n entregadores cujas rotas apresentem a menor distância total, 
    considerando a passagem por algum centro de distribuição que contenha o produto no seu inventário.
    - A entrada da operação deverá ser o pedido, e o resultado uma lista contendo em cada elemento: o 
    entregador, o centro de distribuição, e a lista de segmentos representando a rota.
*/

// struct Path {
//     int deliveryPersonId;           // ID do entregador
//     int distributionCenterId;       // ID do centro de distribuição
//     vector<int> route;              // Lista com os ID's dos vértices que formam a rota
//     int totalDistance;              // Distância total do trajeto

//     bool operator>(const Path& other) const {
//         return totalDistance > other.totalDistance;
//     }
// };

// void dijkstraFromDistributionCente(GraphAdjList& graph, MaxHeap& maxHeap, int startVertexId, int numDeliveryPeople) 
// {
//     // Obtém número |V| de vértices do grafo
//     int m_numVertices = graph.getNumVertices();

//     // Lista "distancia" de tamanho |V| com valores infinito
//     vector<int> distances(m_numVertices, numeric_limits<int>::max());

//     // Lista "parent" de tamanho |V| com valores -1
//     vector<int> parent(m_numVertices, -1);

//     // Lista "visitado" de tamanho |V| com valores falso
//     vector<bool> visited(m_numVertices, false);

//     // Cria uma fila de prioridade heap, ordenando da menor para a maior distância
//     MinHeap heap;

//     // Define distância do vértice inicial como zero
//     distances[startVertexId] = 0;
//     // Coloca o vértice inicial com a sua distância até a origem no topo do heap
//     heap.push({distances[startVertexId], startVertexId});

//     // Cria uma lista para os entregadores selecionado: <distância até o vértice de origem, ID do entregador>
//     vector<pair<int, int>> deliveryPeopleFound;
//     // Número de entregadores selecionados
//     int peopleFound = 0;

//     // Enquanto o heap não está vazio e o número de entregadores selecionados é menor do que o exigido, fazemos:
//     while (!heap.empty() && peopleFound < numDeliveryPeople) {
//         // Removemos o vértice com a menor distância do heap
//         int currentVertexId = heap.top().second;
//         heap.pop();

//         // Se a menor distância 
//         if(maxHeap.top().totalDistance < distances[currentVertexId]) {
//             break;
//         }

//         // Se o vértice atual já foi visitado, ignoramos ele
//         if (visited[currentVertexId]) {
//             continue;
//         }
//         // Define o vértice atual como visitado
//         visited[currentVertexId] = true;

//         // Se a distância do vértice atual é máxima, já visitamos todos os vértices possíveis
//         if (distances[currentVertexId]  == numeric_limits<int>::max()) {
//             break;
//         }

//         // Lista de entregadores no vértice atual
//         vector<DeliveryPerson> deliveryPeople = graph.getVertex(currentVertexId).getDeliveryPeople();

//         // Percorremos a lista deliveryPeople adicionando o entregador a lista de entregadores selecionados 
//         // se o número de entregadores procurado não tiver sido atingido
//         if (!deliveryPeople.empty())
//         {
//             // 'deliveryPerson' é o atual elemento de 'deliveryPeople'
//             for (const DeliveryPerson& deliveryPerson : deliveryPeople) 
//             {
//                 // Adiciona <ID do entregador, distância> à lista de selecionados se ela não estiver cheia
//                 if (peopleFound < numDeliveryPeople) 
//                 {
//                     deliveryPeopleFound.push_back({deliveryPerson.getId(), distances[currentVertexId]});
//                     peopleFound++;
//                 } 
//                 else 
//                 {
//                     break; // Sai do loop se foram encontradas pessoas suficientes
//                 }
//             }
//         }
        
//         // Iterate pelas arestas do vértice atual
//         for (EdgeNode* edge = graph.getEdges(currentVertexId); edge != nullptr; edge = edge->getNext())
//         {
//             // Pega o índice do vértice vizinho
//             int neighborVertexId = edge->otherVertex().getId();

//             // Se o vizinho não foi visitado ainda
//             if(!visited[neighborVertexId])
//             {
//                 // Acessamos o comprimento da aresta
//                 int edgeLength = edge->getLength();

//                 // Se a distância de v1 + comprimento da rua < v2 atual
//                 if (distances[currentVertexId] + edgeLength < distances[neighborVertexId]) 
//                 {
//                     // Atualizamos v2 = distância de v1 + comprimento da rua
//                     distances[neighborVertexId] = distances[currentVertexId] + edgeLength;
//                     // Adicionamos o novo vértice à lista
//                     heap.push({distances[neighborVertexId], neighborVertexId});
//                 }
//             }
//         }
//     }

//     return deliveryPeopleFound;
// }

// vector<Path> findBestDeliveryRoutes(GraphAdjList& graph, 
//                                                      vector<DistributionCenter>& distributionCenters, 
//                                                      Order order, 
//                                                      int numDeliveryPeople) {
    
//     // Id do produto do pedido
//     int productId = order.getProduct().getId();

//     // Cria uma fila de prioridade heap, ordenando da maior para a menor distância
//     MaxHeap maxHeap;

//     // Cria uma lista de caminhos selecionados
//     vector<Path> selectedPaths; 

//     // Percorremos a lista de centros de distribuição adicionando realizando o Dijkstra a partir da posição dele
//     // 'distributionCenter' é o atual elemento de 'distributionCenters'
//     for (const DistributionCenter& distributionCenter : distributionCenters) 
//     {
//         // Adiciona <ID do entregador, distância> à lista de selecionados se ela não estiver cheia
//         if (distributionCenter.isProductAvailable(productId)) 
//         {
//             // Endereço do centro de distribuição
//             int distributionCenterAddress = distributionCenter.getAddress();
//             // Executamos o Dijkstra a partir do centro de distribuição
//             dijkstraFromDistributionCente(GraphAdjList& graph, 
//                                           MaxHeap& maxHeap,
//                                           int distributionCenterAddress, 
//                                           int numDeliveryPeople);
//         }
//     }
//     // Passa os caminhos do encontrados para um vetor 
//     selectedPaths = maxHeap;
//     return selectedPaths
    

//     // selectedPaths now contains the best routes
// }

/*
        OPERAÇÃO 4: sugerir entregas adicionais com base em uma rota.
    - Buscando aproveitar o deslocamento de um entregador em uma rota, proponha uma solução para sugerir 
    pedidos adicionais buscando maximizar o faturamento.
    - Essa solução deverá considerar:
        - A capacidade de transporte do tipo do veículo.
        - O peso e o preço de cada produto.
        - A sua disponibilidade no inventário.
*/


std::pair<double, double> calculateTotalPriceAndWeight(const vector<Order>& orders) {
    double totalPrice = 0.0;
    double totalWeight = 0.0;

    for (const Order& order : orders) {
        totalPrice += order.getProduct().getPrice();
        totalWeight += order.getProduct().getWeight();
    }

    return std::make_pair(totalPrice, totalWeight);
}




vector<Order> GraphOperations::getMaxPriceOrdersLimitedByCenter(Vertex& vertex, double weightLimit, DistributionCenter& distributionCenter) {
        vector<Order> orders = vertex.getCrescentePriceOrders();

        vector<Order> bestCombo;
        double bestPrice = 0.0;

        // Calcula todas as combinações possíveis
        int n = orders.size();
        for (int i = 0; i < (1 << n); ++i) {

            vector<Order> currentCombo;
            double currentWeight = 0.0, currentPrice = 0.0;

            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    Product product = orders[j].getProduct();
                    currentWeight += product.getWeight();
                    currentPrice += product.getPrice();
                    bool productAvalible = distributionCenter.isProductAvailable(product.getId());

                    if (currentWeight <= weightLimit && productAvalible) {
                        currentCombo.push_back(orders[j]);
                    } else {
                        // Se o peso exceder o limite, descarte esta combinação
                        break;
                    }
                }
            }

            if (currentWeight <= weightLimit && currentPrice > bestPrice) {
                bestCombo = currentCombo;
                bestPrice = currentPrice;
            }
        }

        return bestCombo;
}



vector<Order> GraphOperations::findOrdersSugest(GraphAdjList& graph, Route& route){
    

    Order order = route.getOrder();  
    int startVertexId = order.getClientAddress();
    DeliveryPerson deliveryperson = route.getDeliveryPerson();  
    DistributionCenter distributionCenter = route.getDistributionCenter();  

    MinHeap heap;
    
    double capacityAvailableDelivery = deliveryperson.getCurrentCapacityAvailable();
    vector<int> distances(graph.getNumVertices(), INT_MAX);
    vector<bool> visited(graph.getNumVertices(), false);
    vector<vector<Order>> orders(graph.getNumVertices()); // Inicializa um vetor de vetores de Order
    vector<double> totalrevenue(graph.getNumVertices(), 0.0); // Inicializa com zero

    vector<Order> bestOrders;
    double bestValue = 0.0;
    double lowestCost = std::numeric_limits<double>::max();

    distances[startVertexId] = 0;
    heap.push({distances[startVertexId], startVertexId});


    while (!heap.empty()) {
        
        int currentVertexId = heap.top().second; // Vertice com valor minimo
        heap.pop(); // Remove Verice do Heap

        if (distances[currentVertexId] == INT_MAX) { break; }

        if (visited[currentVertexId]) continue;
        visited[currentVertexId] = true;


        EdgeNode* edge = graph.getEdges(currentVertexId);


        while(edge){
            Vertex neighborVertex = edge->otherVertex();
            int neighborVertexId = neighborVertex.getId();
            if (!visited[neighborVertexId]) {
                int edgeLength = edge->getLength();

                if(distances[currentVertexId] + edgeLength < distances[neighborVertexId]){

                    vector<Order> combinedOrders = orders[currentVertexId]; // Herda as ordens do pai

                    double availableCapacity = capacityAvailableDelivery - calculateTotalPriceAndWeight(combinedOrders).first;
                    vector<Order> neighborOrders = getMaxPriceOrdersLimitedByCenter(neighborVertex,availableCapacity,distributionCenter);
                    combinedOrders.insert(combinedOrders.end(), neighborOrders.begin(), neighborOrders.end());

                    orders[neighborVertexId] = combinedOrders;
                    distances[neighborVertexId] = distances[currentVertexId] + edgeLength;

                    // Atualiza as melhores ordens se necessário
                    std::pair<double, double> priceAndWeight = calculateTotalPriceAndWeight(combinedOrders);
                    if (priceAndWeight.first > bestValue || (priceAndWeight.first == bestValue && priceAndWeight.second < lowestCost)) {
                        bestOrders = combinedOrders;
                        bestValue = priceAndWeight.first;
                        lowestCost = priceAndWeight.second;
                    }

                    heap.push({distances[neighborVertexId], neighborVertexId});
                }
            }
            edge = edge->getNext();
        }
    }

    return bestOrders;
}
