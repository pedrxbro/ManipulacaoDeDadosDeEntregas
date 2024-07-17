#include <fstream>
#include <sstream>
#include <iomanip>
#include "entregas.hpp"
using namespace std;


Entrega cadastrarEntrega(string enderecoArq){
    vector<Entrega> entregas = recuperarEntrega(enderecoArq);
    int idLocal;
    for (Entrega entrega : entregas) {
        idLocal = entrega.id;
    }
    
    idLocal++;
    int id; id = idLocal; cin.ignore();
    cout << "Informe o nome: ";   string nome; getline(cin,nome);
    cout << "Informe o endereço: ";   string endereco; getline(cin,endereco);
    cout << "Informe o número: "; string numero; cin >> numero;
    string status = "Pendente";
    int tentativas = 0;
    cin.ignore();
    
    Entrega entrega = {id, nome, endereco, numero, status, tentativas};
    
    return entrega;
}

void imprimirEntrega(Entrega entrega){
    cout << "ID: " << entrega.id << endl;
    cout << "Nome: " << entrega.nome << endl;
    cout << "Endereço: " << entrega.endereco << endl;
    cout << "Número " << entrega.numero << endl;
    cout << "Status: " << entrega.status << endl;
    cout << "Tentativas: " << entrega.tentativas << endl;
}

void registrarEntrega(string enderecoArq, Entrega entrega){
    ofstream arquivo(enderecoArq,ios::app);
    
    if(!arquivo.is_open()){
       cout << "Erro ao abrir o arquivo " << enderecoArq << endl;
       return;
    }  
    arquivo << entrega.id << "," << entrega.nome << ","
     << entrega.endereco << "," << entrega.numero << ","
     << entrega.status << "," << entrega.tentativas << endl;
     cout << endl;
     
    arquivo.close();
}

vector<Entrega> recuperarEntrega(string enderecoArq){
    vector<Entrega> entregas;
    
    ifstream arquivo(enderecoArq);
    string linha;
    
    while(getline(arquivo, linha)){
        stringstream ss(linha);
        string token;
        
        int id;
        string nome, endereco, numero, status;
        int tentativas;
        
        getline(ss, token, ','); id = stoi(token);
        getline(ss, token, ','); nome  = token;
        getline(ss, token, ','); endereco  = token;
        getline(ss, token, ','); numero  = token;
        getline(ss, token, ','); status  = token;
        getline(ss, token, ','); tentativas = stoi(token);

        Entrega entrega = {id, nome, endereco, numero, status, tentativas};
        entregas.push_back(entrega);
        
    }
    arquivo.close();
    return entregas;
}
void realizarEntrega(string enderecoArq) {
    vector<Entrega> entregasPendentes = recuperarEntrega(enderecoArq);
    bool entregasParaProcessar = false;
    
    for (Entrega entrega : entregasPendentes) {
      if (entrega.tentativas >= 3 && entrega.status != "Concluída") {
            entrega.status = "Retornado ao vendedor";
            atualizarEntrega(enderecoArq, entrega);
            continue;
        }
        int resposta;
        if (entrega.status != "Concluída" && entrega.status != "Recusada") {
            entregasParaProcessar = true;
            cout << "=====================================" << endl;
            cout << "         ENTREGAS PENDENTES...       " << endl;
            cout << "=====================================" << endl;
            imprimirEntrega(entrega);
            cout << "1 - Entrega concluída" << endl;
            cout << "2 - Cliente não localizado" << endl;
            cout << "3 - Endereço não localizado" << endl;
            cout << "4 - Cliente recusou" << endl;
            cin >> resposta;

            switch (resposta) {
                case 1:
                    entrega.status = "Concluída";
                    entrega.tentativas += 1;
                    break;
                case 2:
                    entrega.status = "Cliente não localizado";
                    entrega.tentativas += 1;
                    break;
                case 3:
                    entrega.status = "Endereço não localizado";
                    entrega.tentativas += 1;
                    break;
                case 4:
                    entrega.status = "Recusada";
                    entrega.tentativas += 1;
                    break;
                default:
                    cout << "Erro" << endl;
                    break;
            }

        }
        atualizarEntrega(enderecoArq, entrega);
    }
    if(!entregasParaProcessar){
      cout << "=====================================" << endl;
      cout << "     NENHUMA ENTREGA PENDENTE...     " << endl;
      cout << "=====================================" << endl;
    }
}
void atualizarEntrega(string enderecoArq, Entrega entrega){
    vector<Entrega> entregas = recuperarEntrega(enderecoArq);
    ofstream arquivo(enderecoArq);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo " << enderecoArq << endl;
        return;
    }
    //Verifica se o ID atual é o que necessita ser atualizado.
    for (Entrega entre : entregas) {
        if (entre.id == entrega.id) {
            entre = entrega;
        }
        arquivo << entre.id << "," << entre.nome << ","
                << entre.endereco << "," << entre.numero << ","
          << entre.status << "," << entre.tentativas << endl;
    }
    arquivo.close();
}

void medias(string enderecoArq){ 
    vector<Entrega> entregas = recuperarEntrega(enderecoArq);
    
    double nEntregas = 0, nConcluida = 0, nClienteNaoLocalizado = 0;
    double nEndNaoLocalizado = 0, nRecusada = 0, nRetornado = 0, nPendente = 0, um = 0, dois = 0, tres = 0;
    double concluida = 0, clienteNaoLocalizado = 0, endNaoLocalizado = 0, recusada = 0, retornado = 0, pendente = 0;
    
    
     for (Entrega entre : entregas) {
        nEntregas++;
        if (entre.status == "Concluída") nConcluida++;
        else if (entre.status == "Cliente não localizado") nClienteNaoLocalizado++;
        else if (entre.status == "Endereço não localizado") nEndNaoLocalizado++;
        else if (entre.status == "Recusada") nRecusada++;
        else if (entre.status == "Retornado ao vendedor") nRetornado++;
        else if (entre.status == "Pendente") nPendente++;
        
        //Só vai incrementar o numero de tentativas se ainda estiverem no campo de entrega.
        if (entre.status == "Concluída") {
            if (entre.tentativas == 1) um++;
            else if (entre.tentativas == 2) dois++;
            else if (entre.tentativas == 3) tres++;
        }
    }
    concluida = (nConcluida / nEntregas) * 100;
    clienteNaoLocalizado = (nClienteNaoLocalizado / nEntregas) * 100;
    endNaoLocalizado = (nEndNaoLocalizado / nEntregas) * 100;
    recusada = (nRecusada / nEntregas) * 100;
    retornado = (nRetornado / nEntregas) * 100;
    pendente = (nPendente / nEntregas) * 100;
    um = (um / nConcluida) * 100;
    dois = (dois / nConcluida) * 100;
    tres = (tres / nConcluida) * 100;
    
    cout << fixed << setprecision(2);
    cout << "Concluída----------------" << concluida << "%" << endl;
    cout << "Pendente-----------------" << pendente << "%" << endl;
    cout << "Cliente não localizado---" << clienteNaoLocalizado << "%" << endl;
    cout << "Endereço não localizado--" << endNaoLocalizado << "%" << endl;
    cout << "Recusada-----------------" << recusada << "%" << endl;
    cout << "Retornado ao vendedor----" << retornado << "%" << endl;
    cout << "==========================================" << endl;
    cout << "Entregas 1º tentativa----" << um << "%" << endl;
    cout << "Entregas 2º tentativa----" << dois << "%" << endl;
    cout << "Entregas 3º tentativa----" << tres << "%" << endl;
}
