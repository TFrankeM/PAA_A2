#include "../headers/distributioncenter.h"

// Construtor
DistributionCenter::DistributionCenter(const int& centerId)
    : id(centerId) 
{}

// Retorna o ID do centro de distribuição
int DistributionCenter::getId() const 
{
    return id;
}

// Adiciona produto ao inventário
void DistributionCenter::addProduct(Product product, int quantity) 
{
    int productId = product.getId();
    inventory[productId] += quantity;
}

// Remove produto do inventário
void DistributionCenter::removeProduct(const int& productId) 
{
    // Verifica se o produto está no inventário (se não estiver, aponta para null)
    auto it = inventory.find(productId);
    // Se o produto for encontrado no estoque
    if (it != inventory.end()) 
    {
        if (it->second > 1) 
        {
            it->second--;  // Reduz a quantidade em 1 se for maior que 1
        } 
        else 
        {
            inventory.erase(it);  // Remove completamente se for 1
        }
    }
}

// Retorna o inventário
map<int, int> DistributionCenter::getInventory() const 
{
    return inventory;
}

// Retorna se um produto está no inventário do centro de distribuição
bool DistributionCenter::isProductAvailable(const int& productId) const 
{
    auto it = inventory.find(productId);
    return it != inventory.end() && it->second > 0;         // Ele deve estar no CD e com quantidade maio que zero
}

// Retorna o endereço do cliente
int DistributionCenter::getAddress() const 
{
    return address;
}

// Atribui o endereço do cliente
void DistributionCenter::setAddress(const int& address) {
    this->address = address;
}