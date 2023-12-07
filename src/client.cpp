#include "../headers/client.h"

// Construtor da classe Cliente
Client::Client(const string& clientId)
    : id(clientId)
{}

// Retorna o ID do cliente
string Client::getId() const {
    return id;
}

// Adiciona um pedido à lista de pedidos do cliente
void Client::addOrder(const Order& order) {
    orders.push_back(order);
}

// Retorna a lista de pedidos do cliente
vector<Order> Client::getOrders() const {
    return orders;
}

