//---------------------------------------------------------------------
// Arquivo      : escalona.cpp
// Conteudo     : implementacao do tipo Escalona
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "escalona.h"
#include "msgassert.h"
#include <string>

Escalonador::Escalonador(std::string nome_saida)
{
    this->arq_saida.open(nome_saida, std::ofstream::out);
    erroAssert(arq_saida.good(), "Nao foi possivel abrir o arquivo de saida!");
}

void Escalonador::executar_comando(Comando com)
{
    switch (com.get_id())
    {
    case 0: // add_urls
        while(com.more_urls()) {
            this->add_url(com.get_url());
        }
        break;
    case 1: // escalona_tudo
        this->escalona_tudo();
        break;
    case 2: // escalona
        this->escalona(com.get_quantidade());
        break;
    case 3: // escalona_host
        this->escalona_host(com.get_host(), com.get_quantidade());
        break;
    case 4: // ver_host
        this->ver_host(com.get_host());
        break;
    case 5: // lista_hosts
        this->lista_hosts();
        break;
    case 6: // limpa_host
        this->limpa_host(com.get_host());
        break;
    case 7: // limpa_tudo
        this->limpa_tudo();
        break;
    default:
        std::cerr << "Comando invalido: " << com.get_id() << std::endl;
        abort();
    }
}

Escalonador::~Escalonador()
{
    this->arq_saida.close();
}