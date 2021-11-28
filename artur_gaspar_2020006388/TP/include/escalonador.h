//---------------------------------------------------------------------
// Arquivo      : escalona.h
// Conteudo     : definicoes do tipo Escalonador
// Autor        : Artur Gaspar da Silva. (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef ESCALONA
#define ESCALONA

#include <string>
#include <fstream>
#include "comando.h"
#include "fila_hosts.h"

class Escalonador
{
public:
    Escalonador(std::string nome_saida);
    void executar_comando(Comando &com);
    ~Escalonador();

private:
    std::ofstream arq_saida;
    Fila_Hosts fila;

    void add_url(std::string url);
    int escalona_tudo();
    int escalona(int quantidade);
    int escalona_host(std::string host_string, int quantidade);
    int escalona_host_interno(Host_Node *hn, int quantidade);
    void ver_host(std::string host_string);
    void lista_hosts();
    void limpa_host(std::string host_string);
    void limpa_tudo();
};

#endif