//---------------------------------------------------------------------
// Arquivo      : url.cpp
// Conteudo     : implementacao do tipo URL
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "url.h"
#include "msgassert.h"

URL::URL(std::string url)
{
    if (url_valido(url))
        this->url_string = this->url_tratado(url);
    else
        throw std::invalid_argument("Url invalido fornecido.");
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

std::string URL::get_host_string()
{
    // Removendo http://
    std::string resposta = this->url_string.substr(7);

    // Removendo www.
    if (resposta.substr(0, 4) == "www.")
        resposta = resposta.substr(4);

    // Removendo tudo a partir da proxima /
    for (size_t i = 0; i < resposta.size(); i++)
    {
        if (resposta[i] == '/')
        {
            resposta = resposta.substr(0, i);
            break;
        }
    }

    return resposta;
}

bool URL::operator>=(const URL &url)
{
    int n_barras = 0, n_barras_arg = 0;
    for (char c : this->url_string)
        n_barras += (c == '/');
    for (char c : url.url_string)
        n_barras_arg += (c == '/');
    return n_barras >= n_barras_arg;
}

bool URL::url_valido(std::string url)
{
    bool http = url.substr(0, 7) == "http://";
    std::string url2 = this->remove_fragmento(url);
    bool ext_valida = this->extensao_valida(url);

    return http && ext_valida;
}

std::string URL::remove_fragmento(std::string url)
{
    std::string newUrl = "";
    for (char c : url)
        if (c == '#')
            break;
        else
            newUrl += c;

    return newUrl;
}

bool URL::extensao_valida(std::string url_sem_fragmento)
{
    int tamanho = url_sem_fragmento.size();
    if (url_sem_fragmento[url_sem_fragmento.size() - 1] == '/')
        url_sem_fragmento = url_sem_fragmento.substr(0, url_sem_fragmento.size() - 1);
    std::string extensao = url_sem_fragmento.substr(tamanho - 4, 4);
    if (extensao == ".jpg" || extensao == ".gif" || extensao == ".mp3" ||
        extensao == ".avi" || extensao == ".doc" || extensao == ".pdf")
        return false;
    else
        return true;
}

std::string URL::remove_www(std::string url)
{
    if (url.substr(7, 4) == "www.")
        return url.substr(0, 7) + url.substr(11);
    else
        return url;
}

std::string URL::url_tratado(std::string url)
{
    std::string sem_fragmento = this->remove_fragmento(url);
    std::string sem_www = this->remove_www(sem_fragmento);
    std::string resposta;
    if (sem_www[sem_www.size() - 1] == '/')
        resposta = sem_www.substr(0, sem_www.size() - 1);
    else
        resposta = sem_www;
    return resposta;
}