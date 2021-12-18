//---------------------------------------------------------------------
// Arquivo      : comando.cpp
// Conteudo     : implementacao do tipo Comando
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "comando.h"
#include "msgassert.h"
#include <string>
#include <iostream>

int Comando::get_id()
// Descricao: retorna o identificador numérico do tipo de comando.
// Entrada: nenhuma.
// Saida: identificador numérico do tipo de comando da instância.
{
    return this->id_comando;
}

std::string Comando::get_host()
// Descricao: obtém o host do comando, caso seja um comando com argumento de host.
// Entrada: nada.
// Saida: string do host passado como argumento, erro se o comando não possui host como
// argumento.
{
    erroAssert(
        this->id_comando == 3 ||
            this->id_comando == 4 ||
            this->id_comando == 6,
        "O comando desejado nao possui host como argumento.");

    return this->host;
}

bool Comando::more_urls()
// Descricao: informa se ainda há URLs do comando a serem lidos.
// Entrada: nada.
// Saida: verdadeiro se ainda há URLs, falso se não há.
{
    erroAssert(this->id_comando == 0, "O comando desejado nao possui urls como argumento.");

    return this->atual_url_pos < this->quantidade;
}

std::string Comando::get_url()

// Descricao: obtém mais um URL do comando que ainda não foi lido.
// Entrada: nada.
// Saida: o próximo URL a ser lido.
{
    erroAssert(this->id_comando == 0, "O comando desejado nao possui urls como argumento.");
    erroAssert(this->more_urls(), "Nao ha mais URLs a serem lidos.");

    return *this->urls[this->atual_url_pos++];
}

int Comando::get_quantidade()
// Descricao: informa a quantidade de URLs a serem lidos.
// Entrada: nada.
// Saida: a quantidade de URLs ainda não lidos.
{
    erroAssert(
        !(this->id_comando == 0 ||
            this->id_comando == 1),
        "O comando desejado nao possui quantidade como argumento.");

    return this->quantidade;
}

std::istream &operator>>(std::istream &is, Comando &com)
// Descricao: inicaliza um objeto do tipo Comando a partir de dados de uma istream.
// Entrada: istream de onde serão lidos os dados e referência para o Comando a ser instanciado.
// Saida: istream após ler os dados necessários para instanciar o Comando.
{
    std::string nome_comando;
    is >> nome_comando;

    if (is.eof() || !is.good())
        return is;

    // Identifica o comando lido:
    if (nome_comando == "ADD_URLS")
        com.id_comando = 0;
    else if (nome_comando == "ESCALONA_TUDO")
        com.id_comando = 1;
    else if (nome_comando == "ESCALONA")
        com.id_comando = 2;
    else if (nome_comando == "ESCALONA_HOST")
        com.id_comando = 3;
    else if (nome_comando == "VER_HOST")
        com.id_comando = 4;
    else if (nome_comando == "LISTA_HOSTS")
        com.id_comando = 5;
    else if (nome_comando == "LIMPA_HOST")
        com.id_comando = 6;
    else if (nome_comando == "LIMPA_TUDO")
        com.id_comando = 7;
    else
    {
        std::cerr << "Comando invalido: " << nome_comando << std::endl;
        abort();
    }

    // Lê os argumentos do comando lido:
    switch (com.id_comando)
    {
    case 0: // add_urls
        is >> com.quantidade;
        erroAssert(com.quantidade >= 0, "Quantidade de URLs a adicionar invalida.");
        com.urls = (std::string **)malloc(com.quantidade * sizeof(std::string *));

        for (int i = 0; i < com.quantidade; i++)
        {
            com.urls[i] = new std::string;
            is >> *com.urls[i];
        }
        com.atual_url_pos = 0;
        break;
    case 1: // escalona_tudo
        break;
    case 2: // escalona
        erroAssert(com.quantidade >= 0, "Quantidade de URLs a escalonar invalida.");
        is >> com.quantidade;
        break;
    case 3: // escalona_host
        erroAssert(com.quantidade >= 0, "Quantidade de URLs a escalonar invalida.");
        is >> com.host >> com.quantidade;
        break;
    case 4: // ver_host
        is >> com.host;
        break;
    case 5: // lista_hosts
        break;
    case 6: // limpa_host
        is >> com.host;
        break;
    case 7: // limpa_tudo
        break;
    default:
        std::cerr << "Resultado inesperado ao executar " << nome_comando << std::endl;
        abort();
    }

    return is;
}

void Comando::destruir()
// Descricao: libera o espaço possivelmente alocado para o objeto (aplicavel para o
// comando ADD_URLs).
// Entrada: nada.
// Saida: nenhuma.
{
    if (this->urls != nullptr)
    {
        for (int i = 0; i < this->quantidade; i++)
        {
            if (this->urls[i] != nullptr)
            {
                free(this->urls[i]);
                this->urls[i] = nullptr;
            }
        }
        free(this->urls);
        this->urls = nullptr;
    }
}

Comando::~Comando()
// Descricao: destrutor padrão do tipo Comando
// Entrada: nada.
// Saida: nenhuma.
{
    this->destruir();
}