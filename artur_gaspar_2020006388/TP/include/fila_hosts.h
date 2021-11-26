//---------------------------------------------------------------------
// Arquivo      : fila_hosts.h
// Conteudo     : definicoes do tipo fila_hosts
// Autor        : Artur Gaspar da Silva(artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef FILA_HOSTS
#define FILA_HOSTS

#include <string>
#include "host.h"


struct Host_Node{
    Host host;
    Host_Node* anterior;
    Host_Node* proximo;
};

class Fila_Hosts
{
public:
    Fila_Hosts();

    void add_host(Host host);
    Host_Node* get_front_host();
    void remove_front_host();
    Host_Node* get_host(std::string host_string);
    void remove_host(std::string host_string);
    bool vazia();
    void clear();

private:

};

#endif