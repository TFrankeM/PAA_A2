#ifndef DISTRIBUTIONCENTER_H
#define DISTRIBUTIONCENTER_H
#include <map>
#include "product.h"

using namespace std;

/* Distribution Center Header*/
class DistributionCenter {
private:
    int id;                        // Identificador único do centro de distribuição
    map<int, int> inventory;       // Inventário de produtos (id dos produtos) com suas quantidades

public:
    // Construtor
    DistributionCenter(const int& centerId);

    // Métodos de acesso e manipulação do inventário
    int getId() const;                                          // Pega o ID do centro de distribuição
    void addProduct(Product productId, int quantity);         // Adiciona produto
    void removeProduct(const int& productId);                   // Remove produto
    map<int, int> getInventory() const;                         // Obtém inventário
    bool isProductAvailable(const int& productId) const;        // Verifica se um produto está no centro
};

#endif