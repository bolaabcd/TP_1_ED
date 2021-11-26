//---------------------------------------------------------------------
// Arquivo      : url.h
// Conteudo     : definicoes do tipo URL
// Autor        : Artur Gaspar da Silva(artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef URL_CLASSE
#define URL_CLASSE

#include <string>
#include <iostream>

class URL
{
public:
    URL(std::string url);
    friend std::ostream &operator<<(std::ostream &os, URL const &url);
private:
    
};

#endif