//---------------------------------------------------------------------
// Arquivo      : fila_hosts.cpp
// Conteudo     : implementacao do tipo Fila_Hosts
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "fila_hosts.h"

Host_Node::Host_Node(Host host) : host(host)
{
    this->proximo = nullptr;
}

Host_Node::~Host_Node()
{
    this->host.limpar();
}

Fila_Hosts::Fila_Hosts()
{
    this->no_frontal = nullptr;
    tamanho = 0;
}

void Fila_Hosts::add_host(Host host)
{
    if (get_host(host.base_string()) != nullptr)
    {
        return;
    }
    Host_Node *hn = this->no_frontal;
    if (hn == nullptr)
    {
        this->no_frontal = new Host_Node(host);
    }
    else
    {
        while (hn->proximo != nullptr)
        {
            hn = hn->proximo;
        }
        hn->proximo = new Host_Node(host);
    }
    this->tamanho++;
}

Host_Node *Fila_Hosts::get_front_host()
{
    return this->no_frontal;
}

void Fila_Hosts::remove_front_host()
{
    Host_Node *primeiro = this->no_frontal;
    this->no_frontal = this->no_frontal->proximo;
    primeiro->host.limpar();
    delete primeiro;
    this->tamanho--;
}

Host_Node *Fila_Hosts::get_host(std::string host_string)
{
    Host_Node *hn = this->no_frontal;
    while (hn != nullptr && hn->host.base_string() != host_string)
    {
        hn = hn->proximo;
    }
    return hn;
}

void Fila_Hosts::remove_host(std::string host_string)
{
    Host_Node *hn = this->no_frontal;
    Host_Node *hn_anterior = nullptr;
    while (hn != nullptr && hn->host.base_string() != host_string)
    {
        hn_anterior = hn;
        hn = hn->proximo;
    }
    if (hn != nullptr)
    {
        if (hn_anterior == nullptr)
            remove_front_host();
        else
        {
            hn_anterior->proximo = hn->proximo;
            delete hn;
        }

        this->tamanho--;
    }
}

bool Fila_Hosts::vazia()
{
    return this->tamanho == 0;
}

void Fila_Hosts::clear()
{
    while (!vazia())
    {
        remove_front_host();
    }
}

Fila_Hosts::~Fila_Hosts()
{
    this->clear();
}