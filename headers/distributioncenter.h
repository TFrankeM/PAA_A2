#ifndef DISTRIBUTIONCENTER_H
#define DISTRIBUTIONCENTER_H
#include <string>
#include <map>
#include "product.h"

using namespace std;

/* Distribution Center Header*/
class DistributionCenter {
private:
    string id;                        // Identificador único do centro de distribuição
    map<string, int> inventory;       // Inventário de produtos (id dos produtos) com suas quantidades

public:
    // Construtor
    DistributionCenter(const string& centerId);

    // Métodos de acesso e manipulação do inventário
    string getId() const;                                          // Pega o ID do centro de distribuição
    void addProduct(const string& productId, int quantity);        // Adiciona produto
    void removeProduct(const string& productId);                   // Remove produto
    map<string, int> getInventory() const;                         // Obtém inventário
    bool isProductAvailable(const string& productId) const;        // Verifica se um produto está no centro
};

#endif