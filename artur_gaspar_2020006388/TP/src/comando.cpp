//---------------------------------------------------------------------
// Arquivo      : comando.cpp
// Conteudo     : implementacao do tipo Comando
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------
#include "comando.h"
#include "msgassert.h"
#include <string>
#include <iostream>

std::istream& operator >> (std::istream& is, Comando& com){
    std::string nome_comando;
    is >> nome_comando;
    if (nome_comando == "ADD_URLS")           com.id_comando = 0;
    else if (nome_comando == "ESCALONA_TUDO") com.id_comando = 1;
    else if (nome_comando == "ESCALONA")      com.id_comando = 2;  
    else if (nome_comando == "ESCALONA_HOST") com.id_comando = 3;
    else if (nome_comando == "VER_HOST")      com.id_comando = 4;
    else if (nome_comando == "LISTA_HOSTS:")  com.id_comando = 5;
    else if (nome_comando == "LIMPA_HOST")    com.id_comando = 6;
    else if (nome_comando == "LIMPA_TUDO")    com.id_comando = 7;
    else{
        std::cerr << "Comando invalido: " << nome_comando << std::endl;
        abort();
    }
    
    switch (com.id_comando)
    {
    case 0:
        is >> com.quantidade;
        break;
    case 2:
        is >> com.quantidade;
        break;
    case 3:
        is >> com.host >> com.quantidade;
        break;
    case 4:
        is >> com.host;
        break;
    case 6:
        is >> com.host;
        break;
    default:
        std::cerr << "Comando invalido: " << nome_comando << std::endl;
        abort();
    }

    return is;
}