#include "../headers/distributioncenter.h"

// Construtor
DistributionCenter::DistributionCenter(const string& centerId)
    : id(centerId) 
{}

// Retorna o ID do centro de distribuição
string DistributionCenter::getId() const 
{
    return id;
}

// Adiciona produto ao inventário
void DistributionCenter::addProduct(const string& productId, int quantity) 
{
    inventory[productId] += quantity;
}

// Remove produto do inventário
void DistributionCenter::removeProduct(const string& productId) 
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
map<string, int> DistributionCenter::getInventory() const 
{
    return inventory;
}

// Retorna se um produto está no inventário do centro de distribuição
bool DistributionCenter::isProductAvailable(const string& productId) const 
{
    auto it = inventory.find(productId);
    return it != inventory.end() && it->second > 0;         // Ele deve estar no CD e com quantidade maio que zero
}

