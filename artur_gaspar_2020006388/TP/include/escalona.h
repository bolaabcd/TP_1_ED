//---------------------------------------------------------------------
// Arquivo      : escalona.h
// Conteudo     : definicoes do tipo Escalonador
// Autor        : Artur Gaspar da Silva. (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#ifndef ESCALONA
#define ESCALONA

#include <string>
#include "comando.h"

class Escalonador {
    public:
        Escalonador(std::string arquivo_saida);
        void executar_comando(Comando com);
    private:
        void add_url(std::string url);
        void escalona_tudo();
        void escalona();
        void escalona_host();
        void ver_host();
        void lista_hosts();
        void limpa_host();
        void limpa_tudo();

};

#endif