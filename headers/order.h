#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include "product.h"
#include "seller.h"

using namespace std;


// Enum para tipos de pedido
enum class OrderType {
    Simple,
    Optimized
};

/* Order Header*/
class Order {
private:
    int id;                 // Identificado único para pedido
    Product product;        // O produto do pedido
    OrderType type;         // Tipo de pedido
    int sellerAddress;      // Endereço (número do vértice) do vendedor ou CD (-1 enquanto não há vendedor definido)
    int clientAddress;      // Endereço (número do vértice) do cliente

public:
    // Construtor para inicializar um pedido
    Order(const int& orderId, const Product& orderedProduct, OrderType orderType);

    // Métodos de acesso
    int getId() const;              // Pega o ID do pedido
    Product getProduct() const;     // Pega o produto do pedido
    double getTotalWeight() const;  // Método para calcular o peso total do pedido
    OrderType getType() const;      // Pega o tipo do pedido
    int getSellerAddress() const;   // Pega o endereço do vendedor
    int getClientAddress() const;   // Pega o endereço do cliente
};

#endif