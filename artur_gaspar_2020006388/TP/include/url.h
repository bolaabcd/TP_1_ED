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
    std::string as_string();
    friend std::ostream &operator<<(std::ostream &os, URL const &url);
    bool operator>(const URL &url);
    std::string get_host_string();

private:
    std::string url_string;
    bool same_host(URL url);
    bool contida(URL url);
    bool url_valido(std::string url);
    std::string remove_fragmento(std::string url);
    bool extensao_valida(std::string url_sem_fragmento);
    std::string remove_www(std::string url);
    std::string url_tratado(std::string url);
};

#endif