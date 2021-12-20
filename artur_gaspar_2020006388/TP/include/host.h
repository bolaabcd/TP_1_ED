//---------------------------------------------------------------------
// Arquivo      : host.h
// Conteudo     : definicoes do tipo Host
// Autor        : Artur Gaspar da Silva(artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef HOST_CLASSE
#define HOST_CLASSE

#include <string>
#include "url.h"

class URL_Node
{
public:
    URL_Node(URL url);
    URL url;
    URL_Node *proximo;
};

class Host
{
public:
    Host(std::string url);
    std::string base_string();
    void add_url(URL url);
    int get_tamanho();
    URL_Node *get_first_url();
    void remove_first_url();
    bool vazio();
    void limpar();
    ~Host();

private:
    std::string host_string;
    URL_Node *no_frontal;
    int tamanho;
};

#endif