#include "../headers/order.h"

// Implementação do construtor
Order::Order(const int& orderId, const Product& orderedProduct, OrderType orderType, int orderSeller, int orderClient)
    : id(orderId)
    , product(orderedProduct)
    , type(orderType) 
    , sellerAddress(orderSeller)
    , clientAddress(orderClient)
{}

// Retorna o ID do pedido
int Order::getId() const { return id; }

// Retorna o produto do pedido
Product Order::getProduct() const { return product; }

// Retorna o peso do produto do pedido
double Order::getTotalWeight() const { return product.getWeight(); }

// Retorna o tipo do pedido
OrderType Order::getType() const { return type; }

// Retorna o endereço do vendedor (ou do centro de distribuição)
int Order::getSellerAddress() const { return sellerAddress; }

// Retorna o endereço do cliente
int Order::getClientAddress() const { return clientAddress; }