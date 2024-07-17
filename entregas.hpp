#ifndef ENTREGAS_HPP
#define ENTREGAS_HPP
#include <iostream>
#include <vector>
using namespace std;

struct Entrega {
    int id;
    string nome;
    string endereco;
    string numero;
    string status;
    int tentativas;
};


Entrega cadastrarEntrega(string enderecoArq);
void imprimirEntrega(Entrega entrega);
void registrarEntrega(string enderecoArq, Entrega entrega);
vector<Entrega> recuperarEntrega(string enderecoArq);
void atualizarEntrega(string enderecoArq, Entrega entrega);
void realizarEntrega(string enderecoArq);
void medias(string enderecoArq);





#endif
