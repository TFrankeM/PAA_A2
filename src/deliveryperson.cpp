#include <stdexcept>    // Para runtime_error
#include <algorithm>    // Para find_if e remove_if
#include "../headers/deliveryperson.h"

// Construtor da classe entregador
DeliveryPerson::DeliveryPerson(const int& deliveryPersonId, double maxCapacity)
    : id(deliveryPersonId)
    , capacity(maxCapacity) 
{}

// Retorna o ID do entregador
int DeliveryPerson::getId() const { return id; }

// Retorna a capacidade de transporte
double DeliveryPerson::getCapacity() const { return capacity; }

// Atribui uma nova entrega ao entregador
bool DeliveryPerson::assignOrder(const Order& order) 
{
    double orderWeight = order.getTotalWeight();
    if (currentWeight + orderWeight <= capacity) 
    {
        orders.push_back(order);
        currentWeight += orderWeight;
        return true;    // Pedido adicionado
    } 
    else 
    {
        return false;   // Pedido não adicionado devido a excesso de peso
    }
}

// Completa uma entrega e remove ela da lista
void DeliveryPerson::completeOrder(const int& orderId) 
{
    // O algoritmo remove_if encontra e remove uma entrega com ID específico
    auto it = find_if(orders.begin(), orders.end(),
                                [&orderId](const Order& order) {
                                    return order.getId() == orderId;
                                });
    if (it != orders.end()) {
        // Desconta o peso da entrega finalizada do peso total transportado
        currentWeight -= it->getTotalWeight();
        orders.erase(it);
    }
}

// Recupera uma entrega com ID específico
Order DeliveryPerson::getOrder(const int& orderId) const 
{
    // find_if encontra a primeira entrega com ID espefífico
    auto it = find_if(orders.begin(), orders.end(),
                            [&orderId](const Order& order) 
                            {
                                return order.getId() == orderId;
                            });
    if (it != orders.end()) 
    {
        return *it;     // Retorna a ordem encontrada
    }
    throw runtime_error("Order not found"); // Ordem não encontrada, retorna exceção
}