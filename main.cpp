#include <iostream>
#include "entregas.hpp"
using namespace std;
int main ()
{
  int op;
  bool loopOn = true;
  Entrega entrega;
  vector<Entrega> entregas;

  cout << "=====================================" << endl;
  cout << "BEM VINDO AO GERENCIADOR DE ENTREGAS!" << endl;
  cout << "=====================================" << endl;
  
  while(loopOn){
      cout << "Digite o número correspondente à ação: " << endl;
      cout << "1 - Cadastrar entrega: " << endl;
      cout << "2 - Recuperar entregas: " << endl;
      cout << "3 - Realizar entrega: " << endl;
      cout << "4 - Sair" << endl;
      cout << "=====================================" << endl;
      cin >> op;
      
      system("clear");
  
      switch(op){
          case 1:
            cout << "=====================================" << endl;
            cout << "        CADASTRANDO ENTREGA...       " << endl;
            cout << "=====================================" << endl;
            entrega = cadastrarEntrega("./entregas.txt");
            registrarEntrega("./entregas.txt", entrega);
            cout << "=====================================" << endl;
            cout << "    ENTREGA CADASTRADA COM SUCESSO!  " << endl;
            cout << "=====================================" << endl;
          break;
          case 2:
            cout << "=====================================" << endl;
            cout << "       RECUPERANDO ENTREGAS...       " << endl;
            cout << "=====================================" << endl;
            entregas = recuperarEntrega("./entregas.txt");
            for(Entrega entre: entregas){
                imprimirEntrega(entre);
                cout << "--------------------------" << endl;
            }
          break;
          case 3:
            cout << "=====================================" << endl;
            cout << "         ENTREGAS PENDENTES...       " << endl;
            cout << "=====================================" << endl;
            system("clear");
            realizarEntrega("./entregas.txt");
          break;
          case 4:
          cout << "==========================================" << endl;
          cout << "               FINALIZADO.                " << endl;
          cout << "==========================================" << endl;
          medias("./entregas.txt");
          cout << "==========================================" << endl;
          loopOn = false;
          break;
          default:
          cout << "Digite um valor válido" << endl;
          break;
          
          
      }
  }
  return 0;
}
