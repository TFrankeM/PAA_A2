#include "../headers/client.h"

// Construtor da classe Cliente
Client::Client(const int& clientId, const int& clientAddress)
    : id(clientId)
    , address(clientAddress)
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

// Retorna um pedido específico do cliente
Order Client::getOrder(const int& orderId) const {
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i].getId() == orderId)
        {
            return orders[i];
        }
    }
    throw "Pedido não encontrado";
}

// Retorna o endereço do cliente
int Client::getAddress() const {
    return address;
}