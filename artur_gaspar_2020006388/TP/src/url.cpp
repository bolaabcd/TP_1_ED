//---------------------------------------------------------------------
// Arquivo      : url.cpp
// Conteudo     : implementacao do tipo URL
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "url.h"
#include "msgassert.h"

URL::URL(std::string url)
{
    erroAssert(this->url_valido(url), "URL invalido recebido");
    this->url_string = this->url_tratado(url);
}


std::string URL::as_string()
{
    return this->url_string;
}

std::ostream &operator<<(std::ostream &os, URL const &url)
{
    os << url.url_string;
    return os;
}

bool URL::url_valido(std::string url)
{
    return false;
}

std::string URL::url_tratado(std::string url){
    return url;
}