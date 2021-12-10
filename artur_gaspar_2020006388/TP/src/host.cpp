//---------------------------------------------------------------------
// Arquivo      : host.cpp
// Conteudo     : implementacao do tipo Host
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "host.h"

URL_Node::URL_Node(URL url) : url(url)
// Descricao: constrói um nó de URL.
// Entrada: url a ser colocado no nó.
// Saida: objeto instanciado.
{
    this->proximo = nullptr;
}

Host::Host(std::string url)
// Descricao: constrói Host.
// Entrada: um url que pertence ao host a ser criado.
// Saida: objeto instanciado.
{
    this->host_string = URL(url).get_host_string();
    this->no_frontal = nullptr;
    this->tamanho = 0;
}

std::string Host::base_string()
// Descricao: informa a string do host.
// Entrada: nada.
// Saida: string identificadora do host.
{
    return this->host_string;
}

void Host::add_url(URL url)
// Descricao: adiciona um URL ao host.
// Entrada: URL a ser adicionado.
// Saida: nada.
{
    URL_Node *un = this->no_frontal;
    URL_Node *anterior = nullptr;
    if (un == nullptr)
    {
        this->no_frontal = new URL_Node(url);
        this->tamanho++;
        return;
    }

    // Encontrando o primeiro URL que vem depois do que queremos adicionar.
    while (un != nullptr && url >= un->url)
    {
        // Evitando adicionar URLs duplicados.
        if (url.as_string() == un->url.as_string())
            return;
        anterior = un;
        un = un->proximo;
    }

    // Caso em que o novo URL deve ser colocado depois do último.
    if (un == nullptr)
    {
        // Evitando adicionar URLs duplicados.
        if (anterior->url.as_string() == url.as_string())
            return;
        anterior->proximo = new URL_Node(url);
    }
    else
    {
        // Evitando adicionar URLs duplicados.
        if (un->url.as_string() == url.as_string())
            return;
        // Caso que só tem um URL até o momento.
        if (anterior == nullptr)
        {
            URL_Node *seg = this->no_frontal;
            this->no_frontal = new URL_Node(url);
            this->no_frontal->proximo = seg;
        }
        else
        {
            anterior->proximo = new URL_Node(url);
            anterior->proximo->proximo = un;
        }
    }
    this->tamanho++;
}

URL_Node *Host::get_first_url()
// Descricao: informa o nó do primeiro URL em relação à ordem utilizada.
// Entrada: nada.
// Saida: string identificadora do host.
{
    return this->no_frontal;
}

void Host::remove_first_url()
// Descricao: remove o primeiro URL em relação à ordem utilizada.
// Entrada: nada.
// Saida: nenhuma.
{
    URL_Node *primeiro = this->no_frontal;
    this->no_frontal = this->no_frontal->proximo;

    delete primeiro;
    
    this->tamanho--;
}

bool Host::vazio()
// Descricao: informa se o Host ainda possui algum URL.
// Entrada: nada.
// Saida: nenhuma.
{
    return this->tamanho == 0;
}

void Host::limpar()
// Descricao: remove todos URLs do host.
// Entrada: nada.
// Saida: nenhuma.
{
    while (!this->vazio())
    {
        this->remove_first_url();
    }
}

Host::~Host()
// Descricao: destrutor padrão do tipo Host.
// Entrada: nada.
// Saida: nenhuma.
{
    this->limpar();
}