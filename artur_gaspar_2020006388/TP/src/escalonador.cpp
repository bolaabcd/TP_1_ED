//---------------------------------------------------------------------
// Arquivo      : escalona.cpp
// Conteudo     : implementacao do tipo Escalona
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "escalonador.h"
#include "msgassert.h"
#include "host.h"
#include "url.h"

Escalonador::Escalonador(std::string nome_saida)
{
    this->arq_saida.open(nome_saida, std::ofstream::out);
    erroAssert(arq_saida.good(), "Nao foi possivel abrir o arquivo de saida!");
}

void Escalonador::executar_comando(Comando &com)
{
    switch (com.get_id())
    {
    case 0: // add_urls
        while (com.more_urls())
        {
            try
            {
                this->add_url(com.get_url());
            }
            catch (const std::invalid_argument &ia)
            {
            }
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

void Escalonador::destruir(){
    this->arq_saida.close();
    this->limpa_tudo();
}

Escalonador::~Escalonador()
{
    this->destruir();
}

void Escalonador::add_url(std::string url)
{
    URL url_verificado(url);
    Host host_url = Host(url);
    Host_Node *hostPointer = this->fila.get_host(host_url.base_string());

    if (hostPointer == nullptr)
    {
        this->fila.add_host(host_url);
        hostPointer = this->fila.get_host(host_url.base_string());
    }
    hostPointer->host.add_url(url_verificado);
}

int Escalonador::escalona_tudo()
{
    return this->escalona(INT32_MAX);
}

int Escalonador::escalona(int quantidade)
{
    erroAssert(quantidade >= 0, "Quantidade de urls a escalonar invalida.");
    Host_Node *hn = this->fila.get_front_host();
    int amtEsc = 0;

    while (hn != nullptr && amtEsc < quantidade)
    {
        amtEsc += this->escalona_host_interno(hn, quantidade - amtEsc);
        hn = hn->proximo;
    }
    return amtEsc;
}

int Escalonador::escalona_host(std::string host_string, int quantidade)
{
    erroAssert(quantidade >= 0, "Quantidade de URLs a escalonar invalida.");
    Host_Node *hn = this->fila.get_host(host_string);
    if (hn == nullptr)
        return 0;
    else
        return escalona_host_interno(hn, quantidade);
}

int Escalonador::escalona_host_interno(Host_Node *hn, int quantidade)
{
    erroAssert(hn != nullptr, "No de host invalido.");
    int amtEsc = 0;
    while (!hn->host.vazio() && amtEsc < quantidade)
    {
        this->arq_saida << hn->host.get_first_url()->url << std::endl;
        hn->host.remove_first_url();
        amtEsc++;
    }
    return amtEsc;
}

void Escalonador::ver_host(std::string host_string)
{
    URL_Node *un = this->fila.get_host(host_string)->host.get_first_url();
    while (un != nullptr)
    {
        this->arq_saida << un->url.as_string() << std::endl;
        un = un->proximo;
    }
}

void Escalonador::lista_hosts()
{
    Host_Node *hn = this->fila.get_front_host();
    while (hn != nullptr)
    {
        this->arq_saida << hn->host.base_string() << std::endl;
        hn = hn->proximo;
    }
}

void Escalonador::limpa_host(std::string host_string)
{
    Host_Node *no = this->fila.get_host(host_string); 
    erroAssert(no != nullptr, "Host a ser limpo inexistente." );
    no->host.limpar();
}

void Escalonador::limpa_tudo()
{
    this->fila.clear();
}