#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include "product.h"

using namespace std;


// Enum para tipos de pedido
enum class OrderType {
    Simple,
    Optimized
};

/* Order Header*/
class Order {
private:
    int id;          // Identificado único para pedido
    Product product;    // O produto do pedido
    OrderType type;     // Tipo de pedido

public:
    // Construtor para inicializar um pedido
    Order(const int& orderId, const Product& orderedProduct, OrderType orderType);

    // Métodos de acesso
    int getId() const;           // Pega o ID do pedido
    Product getProduct() const;     // Pega o produto do pedido
    double getTotalWeight() const;  // Método para calcular o peso total do pedido
    OrderType getType() const;      // Pega o tipo do pedido
};

#endif