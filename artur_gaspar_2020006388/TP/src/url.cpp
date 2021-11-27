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

std::string URL::get_host_string()
{
    // Removendo http://
    std::string resposta = this->url_string.substr(8, this->url_string.size() - 1);

    // Removendo www.
    if (resposta.substr(0, 4) == "www.")
        resposta = resposta.substr(5, resposta.size());

    // Removendo tudo a partir da proxima /
    for (size_t i = 0; i < resposta.size(); i++)
    {
        if (resposta[i] == '/')
        {
            resposta = resposta.substr(0, i - 1);
            break;
        }
    }

    return resposta;
}

bool URL::same_host(URL url)
{
    return this->get_host_string() == url.get_host_string();
}

bool URL::contida(URL url)
{
    // Verificando se a string contida eh menor que a que a contem
    if(this->url_string.size() < url.url_string.size())
        return false;

    // Obtendo o primeiro caractere que nao pertence ao host
    size_t i;
    std::string host_string = this->get_host_string();
    for (i = 0; i < this->url_string.size() && url.url_string[i] == host_string[i]; i++);

    for(; i < this->url_string.size(); i++){
        if(this->url_string[i] != url.url_string[i])
            return false;
    }

    return true;
}

bool URL::operator<(const URL &url)
{
    if (this->as_string() == url.url_string)
        return false;
    else if (this->same_host(url) && this->contida(url))
        return false;
    else
        return true;
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
    std::string extensao = url_sem_fragmento.substr(tamanho - 4, 4);
    if (extensao == ".jpg" || extensao == ".gif" || extensao == ".mp3" ||
        extensao == ".avi" || extensao == ".doc" || extensao == ".pdf")
        return false;
    else
        return true;
}

std::string URL::remove_www(std::string url)
{
    if (url.substr(8, 4) == "www.")
        return url.substr(0, 7) + url.substr(12);
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