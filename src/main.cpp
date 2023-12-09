#include <iostream>
#include "../headers/txt_reader.h"
#include "../headers/operations.h"
#include <unistd.h>

using namespace std;

void menuPrincipal() 
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "        Bem vindo(a) ao serviço auxiliar de operações da UrbanFast        " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

    cout << "Digite o número correspondente a um cenário de funcionamento do aplicativo:\n" << endl;

    cout << "Cenário 1: \n"
            << "i vértices \n"
            << "j arestas \n"
            << "k clientes \n" 
            << "l entregadores \n"
            << "m vendedores \n"
            << "n centrais de distribuição \n" 
            << endl;

    cout << "Cenário 2: \n"
            << "i vértices \n"
            << "j arestas \n"
            << "k clientes \n" 
            << "l entregadores \n"
            << "m vendedores \n"
            << "n centrais de distribuição \n" 
            << endl;
    
    cout << "Cenário 3: \n"
            << "i vértices \n"
            << "j arestas \n"
            << "k clientes \n" 
            << "l entregadores \n"
            << "m vendedores \n"
            << "n centrais de distribuição \n" 
            << endl;

    cout << "Para sair do aplicativo digite 4\n" << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

    cout << "Digite o número correspondente a um cenário de funcionamento do aplicativo.\n" << endl;
}

GraphAdjList menuOpcoes()
{
    int escolha = 0;
    cout << " ==> Digite a sua escolha [1, 2, 3 ou 4]: ";
    // cin >> escolha;

    escolha = 1;

    switch (escolha) {
        case 1:
        {
            cout << "Excelente opção!!!" << endl; 
            return readFile("./graph_maps/op1/Caso de teste 1.txt");
        }
        case 2:
        {
            cout << "Excelente opção!!!" << endl; 
            // Criar o grafo da cidade com a opção 1
        }
        case 3:
        {
            cout << "Excelente opção!!!" << endl; 
            // Criar o grafo da cidade com a opção 1
        }
        case 4:
        {   
            // Sai do programa
            cout << "Que pena!" << endl; 
        }
        default:
        {
            cout << "Opção inválida. Tente novamente." << endl;
        }
    }

    return GraphAdjList(0);
}

void menuOperacoes()
{
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                                Menu de operações                        " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

    cout << "Operação 1: \n" 
         << "==> Encontrar entregadores próximos \n" << endl;
    
    cout << "Operação 2: \n" 
         << "==> Definir a rota de uma entrega simples \n" << endl; 
    
    cout << "Operação 3: \n" 
         << "==> Definir a rota de uma entrega considerando centros de distribuição \n" << endl; 
    
    cout << "Operação 4: \n" 
         << "==> Sugerir entregas adicionais com base em uma rota \n" << endl; 
}

void escolhaOperacoes(GraphAdjList graph)
{
    int escolha = 0;
    cout << " ==> Digite a sua escolha [1, 2, 3 ou 4]: ";
    //cin >> escolha;
    GraphOperations graphOp;

    escolha = 1;

    switch (escolha) {
        case 1:
        {
            cout << "Excelente opção!!!" << endl; 

            // operação 1
            Client client = graph.getClient(1);
            vector<Order> orders = client.getOrders();
            Order order = orders[0];

            cout << "O pedido " << order.getId() << " do cliente " << client.getId() << " tem como origem o vértice " << order.getSellerAddress() << " e como destino o vértice " << order.getClientAddress() << endl;
            vector<pair<DeliveryPerson, float>> DeliveryPeople = graphOp.findNearestDeliveryPeople(graph, order, 5);

            // Imprime os entregadores mais próximos
            cout << "Os entregadores mais próximos são: " << endl;
            for (int i = 0; i < DeliveryPeople.size(); i++)
            {
                cout << "Entregador " << DeliveryPeople[i].first.getId() << " com distância " << DeliveryPeople[i].second << endl;
            }
        }
        case 2:
        {
            cout << "Excelente opção!!!" << endl; 
            // operação 2
            break;
        }
        case 3:
        {
            cout << "Excelente opção!!!" << endl; 
            // operação 3
            break;
        }
        case 4:
        {
            cout << "Excelente opção!!!" << endl; 
            // operação 4
            break;
        }
        default:
        {
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }
    }
}

int main()
{
    // GraphAdjList g(6);
    // g.addEdge(0, 1, 2);
    // g.addEdge(0, 2, 1);
    // g.addEdge(1, 3, 3);
    // g.addEdge(1, 4, 2);
    // g.addEdge(2, 4, 4);
    // g.addEdge(3, 4, 1);
    // g.addEdge(4, 5, 2);
    // g.addEdge(4, 1, 1);
    // g.print();


    while(true) 
    {
        menuPrincipal();

        int escolha = 0;

        while(true)
        {
            GraphAdjList graph = menuOpcoes();
        
            // Sleep
            sleep(1);

            if(escolha == 1 || escolha == 2 || escolha == 3 || escolha == 4) { break; }

            if(escolha == 4) { break; }

            menuOperacoes();
            escolhaOperacoes(graph);
            sleep(1);
        }
        
        
    }
}

