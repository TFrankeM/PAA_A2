#ifndef CLIENT_H
#define CLIENT_H
#include <vector>
#include "order.h"

using namespace std;

class Client {
private:
    int id;                     // Identificador único do cliente
    vector<Order> orders;       // Pedidos feitos pelo cliente

public:
    // Construtor
    Client(const int& clientId);

    // Métodos de acesso
    int getId() const;                      // Pegar ID do usuário
    void addOrder(const Order& order);      // Adicionar novo pedido do usuário
    vector<Order> getOrders() const;        // Pegar lista de pedidos do usuário
};

#endif