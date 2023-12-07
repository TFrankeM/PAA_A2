#include <iostream>
#include <vector>

using namespace std;

/* Product Header*/
class Product 
{
private:
    string id;          // Identificador único para product
    double price;       // Preço do produto
    double weight;      // Peso do produto

public:
    // Construtor para initializar um objeto Product
    Product(const string& prodId, double prodPrice, double prodWeight);

    // Métodos de acesso para retornar atributos do produto
    string getId() const;         // Pega o product ID
    double getPrice() const;      // Pega o product preço
    double getWeight() const;     // Pega o product peso

    // Métodos de mudança para trocar atributos do produto
    void setPrice(double newPrice);             // Define um novo preço para o produto
    void setWeight(double newWeight);           // Define um novo peso para o produto
};

