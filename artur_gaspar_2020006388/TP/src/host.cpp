//---------------------------------------------------------------------
// Arquivo      : host.cpp
// Conteudo     : implementacao do tipo Host
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "host.h"

URL_Node::URL_Node(URL url) : url(url)
{
    this->proximo = nullptr;
}

Host::Host(std::string url)
{
    this->host_string = get_host_string(url);
    this->no_frontal = nullptr;
    this->tamanho = 0;
}

std::string Host::base_string()
{
    return this->host_string;
}

void Host::add_url(URL url)
{
    URL_Node *un = this->no_frontal;
    URL_Node *anterior = nullptr;
    while (un != nullptr && !(url < un->url))
    {
        anterior = un;
        un = un->proximo;
    }
    if (un == nullptr)
    {
        this->no_frontal = new URL_Node(url);
    }
    else
    {
        if (un->url.as_string() == url.as_string())
            return;
        if (anterior == nullptr)
        {
            URL_Node *seg = this->no_frontal;
            this->no_frontal = new URL_Node(url);
            this->no_frontal->proximo = seg;
        }
        else
        {
            anterior->proximo = new URL_Node(url);
            anterior->proximo->proximo = un;
        }
    }
}

URL_Node *Host::get_first_url()
{
    return this->no_frontal;
}

void Host::remove_first_url()
{
    URL_Node *primeiro = this->no_frontal;
    this->no_frontal = this->no_frontal->proximo;
    delete primeiro;
    this->tamanho--;
}

bool Host::vazio()
{
    return this->tamanho == 0;
}

void Host::limpar()
{
    while (!this->vazio())
    {
        this->remove_first_url();
    }
}

std::string Host::get_host_string(std::string url)
{
    // Removendo http://
    std::string resposta = url.substr(8, url.size() - 1);

    // Removendo www.
    if (resposta.substr(0, 4) == "www.")
        resposta = resposta.substr(5, resposta.size());

    // Removendo tudo a partir da proxima /
    for (int i = 0; i < resposta.size(); i++)
    {
        if (resposta[i] == '/')
        {
            resposta = resposta.substr(0, i - 1);
            break;
        }
    }

    return resposta;
}