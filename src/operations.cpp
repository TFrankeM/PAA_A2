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

// Função para calcular as melhores rotas de entrega
vector<Path> GraphOperations::findBestDeliveryRoutes(GraphAdjList& graph, 
                                                     const Order& order, 
                                                     const vector<DistributionCenter>& distributionCenters, 
                                                     int numDeliveryPeople) 
{
    // Id do produto do pedido
    int productId = order.getProduct().getId();

    // Endereço do cliente
    int clientAddress = order.getClientAddress();

    // Lista de caminhos selecionados
    vector<Path> selectedPaths;

    // Cria um heap ordenando da maior para a menor distância
    MaxHeap heapMaximo;

    // Itera sobre cada centro de distribuição
    for (const DistributionCenter& center : distributionCenters) {
        // Verifica se o produto do pedido está disponível no centro de distribuição
        if (!center.isProductAvailable(productId))
        {
            continue;   // Se não está, ignoramos esse centro
        }

        // Calcula as rotas dos entregadores mais próximos usando Dijkstra
        vector<Path> nearestDeliveryPeople = calculatesDijkstraDistance(graph, 
                                                                       center.getId(), 
                                                                       center.getAddress(), 
                                                                       numDeliveryPeople,
                                                                       clientAddress);

        // Itera sobre os entregadores mais próximos encontrados
        for (const Path& path : nearestDeliveryPeople) {
            // Se a fila de máximos excede o número desejado de entregadores, remove o elemento de maior distância
            if (heapMaximo.getSize() >= numDeliveryPeople) 
            {
                heapMaximo.pop();
            }
            // Insere o elemento na fila de máximos
            heapMaximo.push(path);
        }
    }

    // Transfere as melhores rotas da fila de máximos para o vetor de resultados
    while (!heapMaximo.empty()) {
        selectedPaths.push_back(heapMaximo.top());
        heapMaximo.pop();
    }

    return selectedPaths;
}

// Função para calcular as distâncias dos entregadores usando o algoritmo de Dijkstra
vector<Path> GraphOperations::calculatesDijkstraDistance(GraphAdjList& graph, 
                                                        int distributionCenterID, 
                                                        int centerAddress, 
                                                        int numDeliveryPeople,
                                                        int clientAddress) 
{
    // Define infinito
    const int infinito = numeric_limits<int>::max();

    // Obtém número |V| de vértices do grafo
    int m_numVertices = graph.getNumVertices();

    // Heap minimo
    MinHeap heap;

    // Lista de distâncias dos vértices até centerAddress
    vector<int> distances(m_numVertices, infinito);
    // Lista de vertices visitados
    vector<bool> visited(m_numVertices, false);
    // Lista de vértices pais
    vector<Vertex*> parents(m_numVertices, nullptr);

    // Distância e pai do vértice do centro é 0 e ele mesmo, respectivamente
    Vertex* centerVertex = graph.getVertex(centerAddress);
    distances[centerAddress] = 0;
    parents[centerAddress] = centerVertex;


    heap.push({0, centerVertex});

    // Lista com os entregadores encontrados até o momento
    vector<Path> deliveryPeopleFound;

    // Guardar informações do cliente
    int distanceClient = infinito;
    vector<int> pathClient;

    // Cliente ainda não foi visitado
    bool clientVisited = false;

    // Enquanto o heap não está vazio, o número de entregadores encontrados não é suficiente e 
    // o cliente não foi visitado
    while (!heap.empty() && deliveryPeopleFound.size() < numDeliveryPeople && !clientVisited) {
        // Removemos o vértice com a menor distância do heap
        Vertex* currentVertex = heap.top().second;
        heap.pop();

        // Se o vértice atual já foi visitado, ignoramos ele
        if (visited[currentVertex->getId()]) 
        {
            continue;
        }

        // Define o vértice atual como visitado
        visited[currentVertex->getId()] = true;

        // Se a distância do vértice atual é máxima, já visitamos todos os vértices possíveis
        if (distances[currentVertex->getId()]  == infinito) {
            break;
        }

        // Entregador do vértice atual
        DeliveryPerson* deliveryPerson = currentVertex->getDeliveryPerson();

        // Percorremos a lista deliveryPeople adicionando o entregador a lista de entregadores selecionados 
        // se o número de entregadores procurado não tiver sido atingido

        // Adiciona <Entregador, distância> à lista de selecionados se ela não estiver cheia
        if (deliveryPeopleFound.size() < numDeliveryPeople) 
        {
            // reconstruirRota: reconstroi a rota do centro de distribuição até o entregador (só que no sentido oposto)
            // Salvamos na lista de entregadores
            vector<int> pathToDeliveryPerson = reconstruirRota(parents, currentVertex, centerVertex);
            int totalDistanceToDeliveryPerson = distances[currentVertex->getId()];
            // Salva o entregador, o caminho até ele e a distância total até o momento.
            deliveryPeopleFound.push_back({deliveryPerson->getId(), distributionCenterID, pathToDeliveryPerson, totalDistanceToDeliveryPerson});
        } 
        else 
        {
            break; // Sai do loop se foram encontradas pessoas suficientes
        }
        
        // Se o vértice é o endereço do cliente
        if (currentVertex->getId() == clientAddress) 
        {
            // Ele foi visitado
            clientVisited = true;

            pathClient = reconstruirRota(parents, currentVertex, centerVertex);
            distanceClient = distances[currentVertex->getId()];
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
                int edgeLength = edge->getLength();

                // Se a distância de v1 + comprimento da rua < v2 atual
                if (distances[currentVertex->getId()] + edgeLength < distances[neighborVertex->getId()]) 
                {
                    // Atualizamos v2 = distância de v1 + comprimento da rua
                    distances[neighborVertex->getId()] = distances[currentVertex->getId()] + edgeLength;
                    // Redefinimos o pai do vértice
                    parents[neighborVertex->getId()] = currentVertex;
                    // Adicionamos o novo vértice à lista
                    heap.push({distances[neighborVertex->getId()], neighborVertex});
                }
            }
        }
    }

    // A distância e a rota para o cliente já foram encontradas
    // Agora precisamos adicionar a distância e a rota do cliente a cada entregador encontrado
    for (Path& path : deliveryPeopleFound) {
        // A rota do centro de distribuição até o cliente é adicionada à rota do entregador até o centro de distribuição
        // .insert(position, first, last);
        path.route.insert(path.route.end(), pathClient.begin(), pathClient.end());
        // A distância total é a soma da distância até o centro de distribuição e a distância do centro até o cliente
        path.totalDistance += distanceClient;
    }

    return deliveryPeopleFound;
}

// Função para reconstruir uma rota a partir dos pais dos vértices
vector<int> GraphOperations::reconstruirRota(const vector<Vertex*>& parents, Vertex* vertex, Vertex* centerVertex) 
{
    vector<int> route;

    // Percorre iterativamente adicionando vértice à rota
    while (parents[vertex->getId()]->getId() != centerVertex->getId()) 
    {
        route.push_back(vertex->getId());
        vertex = parents[vertex->getId()];
    }
    route.push_back(centerVertex->getId());

    reverse(route.begin(), route.end());
    return route;
}

/*
        OPERAÇÃO 4: sugerir entregas adicionais com base em uma rota.
    - Buscando aproveitar o deslocamento de um entregador em uma rota, proponha uma solução para sugerir 
    pedidos adicionais buscando maximizar o faturamento.
    - Essa solução deverá considerar:
        - A capacidade de transporte do tipo do veículo.
        - O peso e o preço de cada produto.
        - A sua disponibilidade no inventário.
*/



// Função para filtrar os pedidos disponíveis com base na disponibilidade do produto na distribuidora
vector<Order> filterOrdersByAvailability(const vector<Order>& orders, const DistributionCenter& distributionCenter) {
    vector<Order> availableOrders;

    for (const Order& order : orders) {
        // Obtém o ID do produto do pedido
        int orderProduct = order.getProduct().getId();

        // Verifica se o produto está disponível na distribuidora
        if (distributionCenter.isProductAvailable(orderProduct)) {
            // O produto está disponível na distribuidora, adicione o pedido à lista de pedidos disponíveis
            availableOrders.push_back(order);
        }
    }

    return availableOrders;
}

// Função para ordenar pedidos pelo preço por peso em ordem decrescente
bool orderByPricePerWeight(const Order a, const Order b) {
    // Calcule a taxa de preço por peso para os pedidos 'a' e 'b'
    double rateA = (a.getProduct().getPrice() / a.getProduct().getWeight());
    double rateB = (b.getProduct().getPrice() / b.getProduct().getWeight());

    // Ordene os pedidos pelo preço por peso em ordem decrescente
    return rateA > rateB;
}

// Função para selecionar pedidos que maximizam o preço dentro de um limite de peso
vector<Order> getMaxPriceOrdersLimitedByCenter(const vector<Order> orders, double weightLimit) {
    // Ordene os pedidos pelo preço por peso em ordem decrescente
    vector<Order> sortedOrders = orders;
    std::sort(sortedOrders.begin(), sortedOrders.end(), orderByPricePerWeight);

    vector<Order> selectedOrders;
    double currentWeight = 0.0;
    double totalPrice = 0.0;

    for (const Order order : sortedOrders) {
        if (currentWeight + order.getProduct().getWeight() <= weightLimit) {
            // Se o pedido couber na moto, adicione-o à lista de pedidos selecionados
            selectedOrders.push_back(order);
            currentWeight += order.getProduct().getWeight();
            totalPrice += order.getProduct().getPrice();
        } else {
            // Se o pedido não couber na moto, continue para o próximo pedido
            continue;
        }
    }

    return selectedOrders;
}

// Função para encontrar as melhores ordens com base em uma rota e capacidade disponível
// Esta funcao considera apenas o faturamento (sem custo)
vector<Order> GraphOperations::findOrdersSugest(GraphAdjList& graph, Route& route){

    // Obtém o pedido da rota
    Order order = route.getOrder(); 
    // Obtém o ID do vértice de início do cliente
    int startVertexId = order.getClientAddress();
    // Obtém o vértice de início a partir do ID
    Vertex* startVertex = graph.getVertex(startVertexId);
    // Obtém informações do entregador da rota
    DeliveryPerson deliveryperson = route.getDeliveryPerson();  
    // Obtém informações do centro de distribuição da rota
    DistributionCenter distributionCenter = route.getDistributionCenter();  

    // Cria uma pilha de prioridade (Heap) para a busca
    MinHeap heap;
    
    // Calcula a capacidade disponível de entrega do entregador
    double capacityAvailableDelivery = deliveryperson.getCapacity() - order.getTotalWeight();
    
    // Inicializa vetores para armazenar informações sobre os vértices visitados e pedidos
    vector<int> distances(graph.getNumVertices(), INT_MAX);
    vector<bool> visited(graph.getNumVertices(), false);
    vector<vector<Order>> orders(graph.getNumVertices()); // Inicializa um vetor de vetores de Order
    vector<double> totalrevenue(graph.getNumVertices(), 0.0); // Inicializa com zero

    // Vetores para armazenar as melhores ordens e seu valor
    vector<Order> bestOrders;
    double bestValue = 0.0;

    // Inicializa a distância para o vértice de início como 0 e o adiciona à pilha de prioridade
    distances[startVertexId] = 0;
    heap.push({distances[startVertexId], startVertex});

    // Início da busca
    while (!heap.empty()) {
        
        // Obtém o vértice com a menor distância da pilha de prioridade
        Vertex* currentVertex = heap.top().second; 
        heap.pop(); // Remove o vértice da pilha

        // Se o vértice já foi visitado, continua para o próximo
        if (visited[currentVertex->getId()]) continue;
        visited[currentVertex->getId()] = true;

        // Obtém as arestas do vértice atual
        EdgeNode* edge = graph.getEdges(currentVertex->getId());

        // Itera sobre as arestas
        while(edge){
            // Obtém o vértice vizinho
            Vertex* neighborVertex = edge->otherVertex();
            
            // Se o vizinho não foi visitado
            if (!visited[neighborVertex->getId()]) {
                int edgeLength = edge->getLength();

                // Se a distância atual for menor do que a armazenada, atualiza a distância
                if(distances[currentVertex->getId()] + edgeLength < distances[neighborVertex->getId()]){

                    // Combina as ordens do vértice atual com as do vizinho
                    vector<Order> combinedOrders = orders[currentVertex->getId()];

                    // Calcula a capacidade disponível após a coleta de pedidos no vértice atual
                    double availableCapacity = capacityAvailableDelivery - calculateTotalPriceAndWeight(combinedOrders).first;

                    // Obtém os pedidos do cliente do vértice vizinho
                    Client* neighborVertexClient = neighborVertex->getClient();
                    vector<Order> neighborVertexOrders = neighborVertexClient->getOrders();

                    // Filtra os pedidos disponíveis no centro de distribuição
                    vector<Order> neighborVertexOrdersAvalible = filterOrdersByAvailability(neighborVertexOrders,  distributionCenter);

                    // Seleciona os pedidos com maior preço dentro da capacidade disponível
                    vector<Order> neighborVertexOrdersSelect = getMaxPriceOrdersLimitedByCenter(neighborVertexOrdersAvalible, availableCapacity); 

                    // Combina as ordens do vértice atual com as do vizinho
                    combinedOrders.insert(combinedOrders.end(), neighborVertexOrdersSelect.begin(), neighborVertexOrdersSelect.end());

                    // Armazena as ordens combinadas no vértice vizinho
                    orders[neighborVertex->getId()] = combinedOrders;
                    // Atualiza a distância até o vértice vizinho
                    distances[neighborVertex->getId()] = distances[currentVertex->getId()] + edgeLength;

                    // Atualiza as melhores ordens se necessário
                    std::pair<double, double> priceAndWeight = calculateTotalPriceAndWeight(combinedOrders);
                    if (priceAndWeight.first > bestValue ) {
                        bestOrders = combinedOrders;
                        bestValue = priceAndWeight.first;
                    }

                    // Adiciona o vértice vizinho à pilha de prioridade
                    heap.push({distances[neighborVertex->getId()], neighborVertex});
                }
            }
            edge = edge->getNext();
        }
    }

    // Retorna as melhores ordens encontradas
    return bestOrders;
}

