//---------------------------------------------------------------------
// Arquivo      : fila_hosts_desafio2.h
// Conteudo     : definicoes do tipo Fila_Hosts para desafio 2
// Autor        : Artur Gaspar da Silva(artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef FILA_HOSTS
#define FILA_HOSTS

#include <string>
#include "host.h"

class Host_Node
{
public:
    Host_Node(Host host);
    Host host;
    Host_Node *proximo;
    ~Host_Node();
};

class Fila_Hosts
{
public:
    Fila_Hosts();
    void add_host(Host host);
    Host_Node *get_front_host();
    Host_Node *get_front_host_fixo();
    void set_front_host(Host_Node * hn);
    void remove_front_host();
    Host_Node *get_host(std::string host_string);
    void remove_host(std::string host_string);
    int get_tamanho();
    bool vazia();
    void clear();
    ~Fila_Hosts();

private:
    Host_Node *no_frontal;
    Host_Node *no_frontal_inalterado;
    void add_host_fila_fixa(Host h);
    int tamanho;
};

#endif