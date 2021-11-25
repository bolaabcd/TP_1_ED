//---------------------------------------------------------------------
// Arquivo      : escalona.cpp
// Conteudo     : implementacao do tipo Escalona
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "escalona.h"
#include "msgassert.h"
#include <string>

Escalonador::Escalonador(std::string nome_saida){
    this->arq_saida.open(nome_saida,std::ofstream::out);
    erroAssert(arq_saida.good(),"Nao foi possivel abrir o arquivo de saida!");
}

Escalonador::~Escalonador(){
    this->arq_saida.close();
}