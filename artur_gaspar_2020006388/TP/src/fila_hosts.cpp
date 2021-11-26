//---------------------------------------------------------------------
// Arquivo      : escalona.cpp
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
}

void Fila_Hosts::add_host(Host host)
{
    Host_Node *hn = this->no_frontal;
    if (hn == nullptr)
    {
        hn = new Host_Node(host);
    }
    else
    {
        while (hn->proximo != nullptr)
        {
            hn = hn->proximo;
        }
        hn->proximo = new Host_Node(host);
    }
}

Host_Node *Fila_Hosts::get_front_host()
{
    return this->no_frontal;
}

void Fila_Hosts::remove_front_host()
{
    Host_Node *primeiro = this->no_frontal;
    this->no_frontal = this->no_frontal->proximo;
    delete primeiro;
}

Host_Node *Fila_Hosts::get_host(std::string host_string)
{
}

void Fila_Hosts::remove_host(std::string host_string)
{
}

bool Fila_Hosts::vazia()
{
}

void Fila_Hosts::clear()
{
}