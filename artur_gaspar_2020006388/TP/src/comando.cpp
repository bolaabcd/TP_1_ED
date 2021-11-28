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
{
    return this->id_comando;
}

std::string Comando::get_host()
{
    return this->host;
}

bool Comando::more_urls()
{
    return this->atual_url_pos < this->quantidade;
}

std::string Comando::get_url()
{
    return this->urls[this->atual_url_pos++];
}

int Comando::get_quantidade()
{
    return this->quantidade;
}

std::istream &operator>>(std::istream &is, Comando &com)
{
    std::string nome_comando;
    is >> nome_comando;
    if (is.eof())
        return is;
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

    switch (com.id_comando)
    {
    case 0: // add_urls
        is >> com.quantidade;
        com.urls = (std::string *)malloc(com.quantidade * sizeof(std::string));
        for (int i = 0; i < com.quantidade; i++)
        {
            std::string temp;
            is >> temp;
            com.urls[i] = temp;
        }
        com.atual_url_pos = 0;
        break;
    case 2: // escalona
        is >> com.quantidade;
        break;
    case 3: // escalona_host
        is >> com.host >> com.quantidade;
        break;
    case 4: // ver_host
        is >> com.host;
        break;
    case 6: // limpa_host
        is >> com.host;
        break;
    }

    return is;
}

Comando::~Comando()
{
    if(this->urls != nullptr){
        free(this->urls);
        this->urls = nullptr;
    }
}