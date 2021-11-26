//---------------------------------------------------------------------
// Arquivo      : host.cpp
// Conteudo     : implementacao do tipo Host
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "host.h"

URL_Node::URL_Node(URL url):url(url){
    this->proximo=nullptr;
}

Host::Host(std::string url){
    this->host_string = get_host_string(url);
    this->no_frontal = nullptr;
    this->tamanho = 0;
}

