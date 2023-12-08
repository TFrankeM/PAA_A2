#include "../headers/product.h"

// Constructor da classe produto
Product::Product(const int& prodId, double prodPrice, double prodWeight)
    : id(prodId)
    , price(prodPrice)
    , weight(prodWeight) 
{}

// retorna o produto ID
int Product::getId() const { return id; }

// Retorna o preço do produto
double Product::getPrice() const { return price; }

// Retorna o peso do produto
double Product::getWeight() const { return weight; }

// Atribui o preço do produto
void Product::setPrice(double newPrice) { price = newPrice; }

// Atribui o peso do produto
void Product::setWeight(double newWeight) { weight = newWeight; }

