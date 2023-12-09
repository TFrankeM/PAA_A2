#include "../headers/client.h"

// Construtor da classe Cliente
Client::Client(const int& clientId)
    : id(clientId)
{}

// Retorna o ID do cliente
int Client::getId() const {
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

// Retorna o endereço do cliente
int Client::getAddress() const {
    return address;
}

// Atribui o endereço do cliente
void Client::setAddress(const int& address) {
    this->address = address;
}