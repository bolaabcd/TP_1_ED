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