//---------------------------------------------------------------------
// Arquivo      : host.h
// Conteudo     : definicoes do tipo Host
// Autor        : Artur Gaspar da Silva(artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef HOST_CLASSE
#define HOST_CLASSE

#include <string>
#include "url.h"

class Host
{
public:
    Host(std::string url);
    std::string base_string();
    void add_url(URL url);
    URL get_next_url();
    void remove_next_url();
    bool vazio();
private:
    
};

#endif