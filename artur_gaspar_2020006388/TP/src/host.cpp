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
}

void Host::add_url(URL url)
{
}
URL_Node *Host::get_first_url()
{
}
void Host::remove_first_url()
{
}
bool Host::vazio()
{
}
void Host::limpar()
{
}