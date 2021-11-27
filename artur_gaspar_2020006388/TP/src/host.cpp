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
    this->host_string = URL(url).get_host_string();
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
    this->tamanho++;
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