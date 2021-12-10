//---------------------------------------------------------------------
// Arquivo      : fila_hosts.cpp
// Conteudo     : implementacao do tipo Fila_Hosts
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "fila_hosts.h"

Host_Node::Host_Node(Host host) : host(host)
// Descricao: constrói um nó de hosts.
// Entrada: host a ser colocado no nó.
// Saida: objeto instanciado.
{
    this->proximo = nullptr;
}

Host_Node::~Host_Node()
// Descricao: destrutor padrão de nó de hosts.
// Entrada: nada.
// Saida: nenhuma.
{
    this->host.limpar();
}

Fila_Hosts::Fila_Hosts()
// Descricao: constrói uma fila de hosts.
// Entrada: nada.
// Saida: objeto instanciado.
{
    this->no_frontal = nullptr;
    tamanho = 0;
}

void Fila_Hosts::add_host(Host host)
// Descricao: adiciona um host à fila, caso já não esteja presente.
// Entrada: host a ser colocado na fila.
// Saida: nenhuma.
{
    // Note que ignoramos a re-adição de hosts já presentes, ao invés de gerar erro.
    if (this->get_host(host.base_string()) != nullptr)
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
// Descricao: obtém o primeiro host.
// Entrada: nada.
// Saida: primeiro host da fila.
{
    return this->no_frontal;
}

void Fila_Hosts::remove_front_host()
// Descricao: remove o primeiro host da fila.
// Entrada: nada.
// Saida: nenhuma.
{
    Host_Node *primeiro = this->no_frontal;
    this->no_frontal = this->no_frontal->proximo;

    primeiro->host.limpar();
    delete primeiro;
    
    this->tamanho--;
}

Host_Node *Fila_Hosts::get_host(std::string host_string)
// Descricao: obtém o nó correspondente ao host desejado, via busca linear.
// Entrada: string do host desejado.
// Saida: nó do host em questão.
{
    Host_Node *hn = this->no_frontal;
    while (hn != nullptr && hn->host.base_string() != host_string)
    {
        hn = hn->proximo;
    }
    return hn;
}

void Fila_Hosts::remove_host(std::string host_string)
// Descricao: remove um host da fila, se presente.
// Entrada: host a ser retirado da fila.
// Saida: nenhuma.
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
            hn->host.limpar();
            delete hn;
        }

        this->tamanho--;
    }
}

bool Fila_Hosts::vazia()
// Descricao: informa se a fila está vazia
// Entrada: nada.
// Saida: true se a fila está vazia, falso caso contrário.
{
    return this->tamanho == 0;
}

void Fila_Hosts::clear()
// Descricao: remove todos os hosts da fila.
// Entrada: nada.
// Saida: nenhuma.
{
    while (!vazia())
    {
        remove_front_host();
    }
}

Fila_Hosts::~Fila_Hosts()
// Descricao: destrutor padrão da fila de hosts.
// Entrada: nada.
// Saida: nenhuma.
{
    this->clear();
}