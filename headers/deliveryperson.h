#ifndef DELIVERYPERSON_H
#define DELIVERYPERSON_H
#include <iostream>
#include <vector>
#include "order.h"

using namespace std;

/* DeliveryPerson Header*/
class DeliveryPerson
{
private:
    int id;              // Identificador único para o entregador(a)
    double capacity;        // Peso máximo de produtos que pode carregar
    double currentWeight;   // Peso atual sendo transportado
    vector<Order> orders;   // Lista de pedidos atribuidos ao entregador

public:
    // Contrutor para inicializar um objeto DeliveryPerson
    DeliveryPerson(const int& deliveryPersonId, double maxCapacity);

    // Método de acesso
    int getId() const;           // Pega o ID do entregador
    double getCapacity() const;     // Pega a capacidade máxima do entregador

    // Métodos aplicados na lista de pedidos
    bool assignOrder(const Order& order);          // Atribui um novo pedido ao entregador
    void completeOrder(const int& orderId);     // Completa e remove um pedido da lista
    Order getOrder(const int& orderId) const;   // Retorna um pedido pelo ID
};

#endif