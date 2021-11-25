//---------------------------------------------------------------------
// Arquivo      : comando.h
// Conteudo     : definicoes do tipo Comando
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef COMANDO
#define COMANDO

#include <iostream>
#include <string>
#include <fstream>

class Comando{
    public:
        Comando();
        friend std::istream& operator >> (std::istream& is, Comando& com);

    private:
        int id_comando;
        std::string host;
        int quantidade;
};


#endif