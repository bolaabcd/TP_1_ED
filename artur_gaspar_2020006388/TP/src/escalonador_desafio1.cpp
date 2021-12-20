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
// Descricao: constrói o tipo escalonador a partir do arquivo de saída, que é aberto aqui.
// Entrada: caminho do arquivo de saída.
// Saida: objeto Escalonador instanciado.
{
    this->arq_saida.open(nome_saida, std::ofstream::out);

    erroAssert(arq_saida.good(), "Nao foi possivel abrir o arquivo de saida!");
}

void Escalonador::executar_comando(Comando &com)
// Descricao: executa um comando.
// Entrada: objeto do tipo Comando representando o comando a ser executado.
// Saida: depende do comando, alguns imprimem algo no arquivo de saída, outros só deletam
// URLs, por exemplo.
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

void Escalonador::destruir()
// Descricao: fecha o arquivo de saída e limpa a fila de hosts.
// Entrada: nada.
// Saida: nenhuma.
{
    this->arq_saida.close();
    this->limpa_tudo();
}

Escalonador::~Escalonador()
// Descricao: destrutor padrão do tipo Escalonador.
// Entrada: nada.
// Saida: nenhuma.
{
    this->destruir();
}

void Escalonador::add_url(std::string url)
// Descricao: executa o comando de adicionar URL.
// Entrada: string correspondente à URL a ser adicionada.
// Saida: nenhuma.
{
    // Inicializa os tipos adequados e procura o host.
    URL url_verificado(url);
    Host host_url = Host(url);
    Host_Node *hostPointer = this->fila.get_host(host_url.base_string());

    // Adiciona o host se ele não está presente, e adiciona o URL.
    if (hostPointer == nullptr)
    {
        this->fila.add_host(host_url);
        hostPointer = this->fila.get_host(host_url.base_string());
    }
    hostPointer->host.add_url(url_verificado);
}

int Escalonador::escalona_tudo()
// Descricao: escalona todas as URLs presentes (imŕime em ordem no arquivod de saída e
// deleta do Escalonador).
// Entrada: nada.
// Saida: quantidade de URLs escalonadas.
{
    // Escalonamos até 2147483647 URLs, que provavelmente é mais que o suficiente, já que
    // cada URL tem pelo menos 7 bytes ("http://"), passar esse limite exigiria mais que 14Gb.
    return this->escalona(INT32_MAX);
}

int Escalonador::escalona(int quantidade)
// Descricao: escalona no máximo <quantidade> URLs (imŕime em ordem no arquivod de saída e
// deleta do Escalonador).
// Entrada: quantidade máxima a ser escalonada.
// Saida: quantidade de URLs efetivamente escalonadas.
{
    erroAssert(quantidade >= 0, "Quantidade de urls a escalonar invalida.");
    Host_Node *hn = this->fila.get_front_host();
    int amtEsc = 0;

    // Escalona em BFS cada um dos hosts em ordem, até a quantidade atingir o quanto queremos,
    // ou os URLs presentes acabarem.
    int amtEscPrev = amtEsc;
    while (amtEsc < quantidade)
    {
        amtEsc += this->escalona_host_interno(hn, 1);
        hn = hn->proximo;
        if(hn == nullptr) {
            if(amtEsc == amtEscPrev)
                break;
            hn = this->fila.get_front_host();
            amtEscPrev = amtEsc;
        }
    }
    return amtEsc;
}

int Escalonador::escalona_host(std::string host_string, int quantidade)
// Descricao: escalona no máximo <quantidade> URLs do host (imŕime em ordem no arquivod
// de saída e deleta do Escalonador).
// Entrada: quantidade máxima a ser escalonada e string do host do qual devemos escalonar.
// Saida: quantidade de URLs efetivamente escalonadas.
{
    erroAssert(quantidade >= 0, "Quantidade de URLs a escalonar invalida.");
    Host_Node *hn = this->fila.get_host(host_string);
    // Note que simplesmente ignoramos hosts inválidos ao invés de gerar erro.
    if (hn == nullptr)
        return 0;
    else
        return escalona_host_interno(hn, quantidade);
}

int Escalonador::escalona_host_interno(Host_Node *hn, int quantidade)
// Descricao: escalona no máximo <quantidade> URLs do host do nó (imŕime em ordem no
// arquivo de saída e deleta do Escalonador).
// Entrada: quantidade máxima a ser escalonada e nó do host cujas URLs devemos escalonar.
// Saida: quantidade de URLs efetivamente escalonadas.
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
// Descricao: imprime todas URLs do host em ordem, mas não deleta.
// Entrada: string do host em questão.
// Saida: nenhuma.
{
    Host_Node* hn = this->fila.get_host(host_string);
    avisoAssert(hn != nullptr, "Host pedido inexistente! Ignorando comando.");
    if(hn == nullptr)
        return;
    
    URL_Node *un = this->fila.get_host(host_string)->host.get_first_url();
    while (un != nullptr)
    {
        this->arq_saida << un->url.as_string() << std::endl;
        un = un->proximo;
    }
}

void Escalonador::lista_hosts()
// Descricao: imprime no arquivo de saída todos hosts em ordem.
// Entrada: nada.
// Saida: nenhuma.
{
    Host_Node *hn = this->fila.get_front_host();
    while (hn != nullptr)
    {
        this->arq_saida << hn->host.base_string() << std::endl;
        hn = hn->proximo;
    }
}

void Escalonador::limpa_host(std::string host_string)
// Descricao: deleta todas URLs do host.
// Entrada: nome do host em questão.
// Saida: nenhuma.
{
    Host_Node *no = this->fila.get_host(host_string);
    erroAssert(no != nullptr, "Host a ser limpo inexistente.");
    no->host.limpar();
}

void Escalonador::limpa_tudo()
// Descricao: deleta todas URLs e hosts do Escalonador.
// Entrada: nada.
// Saida: nenhuma.
{
    this->fila.clear();
}