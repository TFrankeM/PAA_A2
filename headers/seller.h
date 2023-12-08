#ifndef SELER_H
#define SELER_H
#include <iostream>
#include <vector>
#include "product.h"

using namespace std;

/* Seller Header*/
class Seller 
{
private:
    string id;                  // Identificador único para seller
    vector<Product> catalog;    // Uma lista de produtos que o vendedor oferece

public:
    // Construtor para inicializar um objeto Seller
    Seller(const string& sellerId);

    // Métodos de acesso para retornar atributos seller ID
    string getId() const;

    // Métodos de mudança para trocar atributos do produto
    void addProduct(const Product& product);            // Adiciona novo produto
    void removeProduct(const string& productId);        // Remove produto
    Product getProduct(const string& productId) const;  // Pega produto
};

#endif