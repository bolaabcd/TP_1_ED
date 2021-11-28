//---------------------------------------------------------------------
// Arquivo      : main.cpp
// Conteudo     : implementacao do programa escalonador
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

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

std::string getNomeSaida(std::string nome_entrada)
{
    size_t pos_ext = nome_entrada.find_last_of('.');
    return nome_entrada.substr(0, pos_ext) + "-out" + nome_entrada.substr(pos_ext);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        uso();
        exit(1);
    }

    std::string nome_entrada(argv[1]);
    std::ifstream arq_entrada;
    arq_entrada.open(nome_entrada, std::ifstream::in);
    erroAssert(arq_entrada.good(), "Nao foi possivel abrir o arquivo de entrada!");

    std::string nome_saida(getNomeSaida(nome_entrada));

    Escalonador escal(nome_saida);
    Comando com;
    while (arq_entrada >> com)
    {
        escal.executar_comando(com);
        // com.~Comando();
    }

    escal.~Escalonador();
    arq_entrada.close();
    return 0;
}