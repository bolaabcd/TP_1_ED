//---------------------------------------------------------------------
// Arquivo      : url.cpp
// Conteudo     : implementacao do tipo URL
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include "url.h"
#include "msgassert.h"

URL::URL(std::string url)
// Descricao: constrói um URL a partir da string, se for válida.
// Entrada: string do url a ser colocado no nó.
// Saida: objeto instanciado.
{
    if (url_valido(url))
        this->url_string = this->url_tratado(url);
    else
        throw std::invalid_argument("URL invalido fornecido.");
}

std::string URL::as_string()
// Descricao: retorna a URL em sua forma de string, já tratado.
// Entrada: nada
// Saida: string do URL, já tratado.
{
    return this->url_string;
}

std::ostream &operator<<(std::ostream &os, URL const &url)
// Descricao: escreve numa ostream o URL em questão.
// Entrada: ostream onde será escrito, e o URL a ser escrito.
// Saida: ostream depois de ter o URL escrito.
{
    os << url.url_string;
    return os;
}

std::string URL::get_host_string()
// Descricao: retorna a string correspondente ao Host da URL.
// Entrada: nada.
// Saida: string correspondente ao host.
{
    erroAssert(this->url_string.length() >= 7,
               "Tamanho da URL pequeno demais para ter 'http://'.");
    
    // Removendo "http://"
    std::string resposta = this->url_string.substr(7);

    // Removendo "www."
    if (resposta.substr(0, 4) == "www.")
        resposta = resposta.substr(4);

    // Removendo tudo a partir da proxima /
    for (size_t i = 0; i < resposta.size(); i++)
    {
        if (resposta[i] == '/')
        {
            resposta = resposta.substr(0, i);
            break;
        }
    }

    return resposta;
}

bool URL::operator>=(const URL &url)
// Descricao: compara dois URLs segundo a ordem especificada.
// Entrada: URL a comparar com a instância atual.
// Saida: verdadeiro se a instância atual deve ser considerada maior ou igual que o argumento.
{
    int n_barras = 0, n_barras_arg = 0;
    for (char c : this->url_string)
        n_barras += (c == '/');
    for (char c : url.url_string)
        n_barras_arg += (c == '/');
    
    return n_barras >= n_barras_arg;
}

bool URL::url_valido(std::string url)
// Descricao: informa se o URL identificado pela string é válido.
// Entrada: string a verificar.
// Saida: verdadeiro se a string é um URL válido, falso se não é.
{
    // Verificando se o URL possui "http://" e extensão válida se ignorarmos fragmento e "/"
    // no final.
    bool http = url.substr(0, 7) == "http://";
    std::string url2 = this->remove_fragmento(url);
    bool ext_valida = this->extensao_valida(url);

    return http && ext_valida;
}

std::string URL::remove_fragmento(std::string url)
// Descricao: remove o fragmento de uma string.
// Entrada: string do url antes de remover possíveis fragmentos.
// Saida: string do url sem fragmento.
{
    std::string newUrl = "";
    for (char c : url)
        if (c == '#')
            break;
        else
            newUrl += c;

    return newUrl;
}

bool URL::extensao_valida(std::string url_sem_fragmento)
// Descricao: informa se o url possui extensão válida.
// Entrada: string de url com fragmento já removido.
// Saida: falso se possui extensão inválida, verdadeiro caso contrário.
{
    erroAssert(url_sem_fragmento.find_first_of('#') == size_t(-1),
               "URL passado na verificacao de extensao possui fragmento");
    
    int tamanho = url_sem_fragmento.size();
    if (url_sem_fragmento[url_sem_fragmento.size() - 1] == '/')
        url_sem_fragmento = url_sem_fragmento.substr(0, url_sem_fragmento.size() - 1);

    erroAssert(tamanho - 4 >= 0, "Tamanho do url invalido (menor que 5).");
    std::string extensao = url_sem_fragmento.substr(tamanho - 4, 4);
    if (extensao == ".jpg" || extensao == ".gif" || extensao == ".mp3" ||
        extensao == ".avi" || extensao == ".doc" || extensao == ".pdf")
        return false;
    else
        return true;
}

std::string URL::remove_www(std::string url)
// Descricao: remove o "www." da string.
// Entrada: string de url.
// Saida: string de url sem o "www.".
{
    erroAssert(url.length() >= 7,
               "Tamanho da URL pequeno demais para ter 'http://'.");

    // Note que se a condição abaixo é satisfeita, temos pelo menos "http://www.", um total
    // de 11 caracteres e portanto o método substr não gera erro.
    if (url.substr(7, 4) == "www.")
        return url.substr(0, 7) + url.substr(11);
    else
        return url;
}

std::string URL::url_tratado(std::string url)
// Descricao: retorna a string de url depois de tratada.
// Entrada: string de url a ser tratada.
// Saida: string de url após tratamento.
{
    std::string sem_fragmento = this->remove_fragmento(url);
    std::string sem_www = this->remove_www(sem_fragmento);
    std::string resposta;
    
    if (sem_www[sem_www.size() - 1] == '/')
        resposta = sem_www.substr(0, sem_www.size() - 1);
    else
        resposta = sem_www;
    return resposta;
}