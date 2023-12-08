#include "../headers/order.h"

// Implementação do construtor
Order::Order(const int& orderId, const Product& orderedProduct, OrderType orderType)
    : id(orderId)
    , product(orderedProduct)
    , type(orderType) 
{}

// Retorna o ID do pedido
int Order::getId() const { return id; }

// Retorna o produto do pedido
Product Order::getProduct() const { return product; }

// Retorna o peso do produto do pedido
double Order::getTotalWeight() const { return product.getWeight(); }

// Retorna o tipo do pedido
OrderType Order::getType() const { return type; }

