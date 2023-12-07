#include <stdexcept>    // Para runtime_error
#include <algorithm>    // Para find_if e remove_if
#include "../headers/seller.h"

// Construtor da classe vendedor
Seller::Seller(const string& sellerId)
    : id(sellerId)
{}

// Retorna o ID do vendedor
string Seller::getId() const { return id; }

// Adiciona novo produto ao catálogo do vendedor
void Seller::addProduct(const Product& product) 
{
    catalog.push_back(product);
}

// Remove um produto do catálogo do vendedor pelo seu ID
void Seller::removeProduct(const string& productId) 
{
    // O algoritmo remove_if reorganiza os elementos no intervalo [begin, end)
    // e retorna um iterador para o novo final desse intervalo.
    // Aqui, ele remove o produto cujo ID corresponde ao productId especificado.
    catalog.erase(remove_if(catalog.begin(), catalog.end(),
                                [&productId](const Product& product) 
                                {
                                    return product.getId() == productId;
                                }),
                                catalog.end());
}

// Recupera um produto do catálogo do vendedor pelo seu ID
Product Seller::getProduct(const string& productId) const 
{
    // O algoritmo find_if procura por um elemento para o qual o fornecido
    // predicado retorna verdadeiro e retorna um iterador para ele.
    // Aqui, procura um produto com o productId especificado.
    // A função lambda verifica se o ID do produto corresponde ao productId especificado.
    auto it = find_if(catalog.begin(), catalog.end(),
                                [&productId](const Product& product) 
                                {
                                    return product.getId() == productId;
                                });
    if (it != catalog.end()) 
    {
        return *it;
    }
    throw runtime_error("Product not found");
}

