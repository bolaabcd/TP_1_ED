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
#include "fila.h"

class Escalonador
{
public:
    Escalonador(std::string nome_saida);
    void executar_comando(Comando com);
    ~Escalonador();

private:
    std::ofstream arq_saida;
    Fila fila;

    void add_url(std::string url);
    void escalona_tudo();
    void escalona(int quantidade);
    void escalona_host(std::string host, int quantidade);
    void ver_host(std::string host);
    void lista_hosts();
    void limpa_host(std::string host);
    void limpa_tudo();
};

#endif