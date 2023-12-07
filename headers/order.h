#include <string>
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
    string id;          // Identificado único para pedido
    Product product;    // O produto do pedido
    OrderType type;     // Tipo de pedido

public:
    // Construtor para inicializar um pedido
    Order(const string& orderId, const Product& orderedProduct, OrderType orderType);

    // Métodos de acesso
    string getId() const;           // Pega o ID do pedido
    Product getProduct() const;     // Pega o produto do pedido
    double getTotalWeight() const;  // Método para calcular o peso total do pedido
    OrderType getType() const;      // Pega o tipo do pedido
};

