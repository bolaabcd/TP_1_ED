#include <iostream>
#include <fstream>
#include "msgassert.h"
#include "escalona.h"
#include "comando.h"

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando

{
    std::cerr << "escalonador" << std::endl;
    std::cerr << "\t<arq>\t\t(nome do arquivo de entrada, argumento obrigatorio)" << std::endl;
}

std::string getNomeSaida(std::string nome_entrada) {
    return nome_entrada;
}

bool checkNomeValido(std::string nome_entrada) {

    return true;
}

int main(int argc, char** argv) {
    if(argc!=2)
        uso();
    erroAssert(checkNomeValido(argv[1]), "Nome de arquivo invalido.");

    std::string nome_entrada(argv[1]);
    std::ifstream arq_entrada;
    arq_entrada.open(nome_entrada,std::ifstream::in);
    erroAssert(arq_entrada.good(),"Nao foi possivel abrir o arquivo de entrada!");

    std::string nome_saida(getNomeSaida(nome_entrada));
    // std::ofstream arq_saida;
    // arq_saida.open(nome_saida,std::ofstream::out);
    // erroAssert(arq_saida.good(),"Nao foi possivel abrir o arquivo de saida!");

    Escalonador escal;
    Comando com(nome_saida);
    while(arq_entrada >> com){
        com.executar();
    }

    arq_entrada.close();
    return 0;
}