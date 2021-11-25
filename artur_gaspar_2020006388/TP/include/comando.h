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
        Comando(){};
        int get_id();
        std::string get_host();
        bool more_urls();
        std::string get_url();
        int get_quantidade();
        friend std::istream& operator >> (std::istream& is, Comando& com);
        ~Comando();
    private:
        int id_comando;
        std::string host;
        std::string* urls;
        int quantidade;
        int atual_url_pos;
};


#endif