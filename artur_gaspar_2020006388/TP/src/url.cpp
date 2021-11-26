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
    bool http = url.substr(0, 7) == "http://";
    std::string url2 = this->remove_fragmento(url);
    bool ext_valida = this->extensao_valida(url);

    return http && ext_valida;
}

std::string remove_fragmento(std::string url)
{
    std::string newUrl = "";
    for (char c : url)
        if (c == '#')
            break;
        else
            newUrl += c;

    return newUrl;
}

bool extensao_valida(std::string url_sem_fragmento)
{
    int tamanho = url_sem_fragmento.size();
    std::string extensao = url_sem_fragmento.substr(tamanho - 4, 4);
    if (extensao == ".jpg" || extensao == ".gif" || extensao == ".mp3" ||
        extensao == ".avi" || extensao == ".doc" || extensao == ".pdf")
        return false;
    else
        return true;
}

std::string URL::url_tratado(std::string url)
{
    return this->remove_fragmento(url);
}