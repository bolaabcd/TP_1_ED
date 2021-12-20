//---------------------------------------------------------------------
// Arquivo      : main.cpp
// Conteudo     : implementacao do programa escalonador
// Autor        : Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <getopt.h>
#include "msgassert.h"
#include "memlog.h"
#include "escalonador.h"
#include "comando.h"


// variavel globais para opcoes
int regmem;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    std::cerr << "escalonador" << std::endl;
    std::cerr << "\t<arq>\t\t(nome do arquivo de entrada, argumento obrigatorio, deve vir antes das opcoes)" << std::endl;
    std::cerr << "\t-l \t\t(registrar padrao de acesso e localidade, opcional, deve vir depois de <arq>)" << std::endl;
}

void parse_args(int argc, char **argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis.
// Entrada: argc e argv.
// Saida: regmem.
{
  // tratando caso de nao ter argumentos
  if (argc == 1)
  {
    uso();
    exit(1);
  }

  // variavel auxiliar
  int c;

  // inicializacao variaveis globais para opcoes
  regmem = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  while ((c = getopt(argc, argv, "l")) != EOF)
  {
    switch (c)
    {
    case 'l':
      regmem = 1;
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }
  }
}

std::string get_nome_saida(std::string nome_entrada)
// Descricao: gera o nome do arquivo de saída.
// Entrada: nome do arquivo de entrada.
// Saida: nome do arquivo de saída.
{
    size_t pos_ext = nome_entrada.find_last_of('.');
    erroAssert(pos_ext != size_t(-1), "Nome de entrada invalido por nao possuir extensao.");
    return nome_entrada.substr(0, pos_ext) + "-out" + nome_entrada.substr(pos_ext);
}

std::string get_nome_registro(std::string nome_entrada)
// Descricao: gera o nome do arquivo de registro.
// Entrada: nome do arquivo de entrada.
// Saida: nome do arquivo de registro.
{
    size_t pos_ext = nome_entrada.find_last_of('.');
    erroAssert(pos_ext != size_t(-1), "Nome de entrada invalido por nao possuir extensao.");
    return nome_entrada.substr(0, pos_ext) + "-log" + nome_entrada.substr(pos_ext);

}

int main(int argc, char **argv)
// Descricao: método principal do programa escalonar.
// Entrada: argc e argv.
// Saida: no arquivo especificado esqueve o resultado das operações especificadas.
{
  if(argc == 1) {
    uso();
    exit(1);
  }
  // Inicializando arquivos e objetos principais.
  std::string nome_entrada(argv[1]);
  std::ifstream arq_entrada;
  arq_entrada.open(nome_entrada, std::ifstream::in);
  erroAssert(arq_entrada.good(), "Nao foi possivel abrir o arquivo de entrada!");

  std::string nome_saida(get_nome_saida(nome_entrada));

  Escalonador escal(nome_saida);
  Comando com;

  parse_args(argc, argv);
  
  // iniciar registro de acesso
  iniciaMemLog(get_nome_registro(nome_entrada),regmem);

  // ativar registro de acesso
  ativaMemLog();

  // Executando comandos
  while (arq_entrada >> com)
  {
      escal.executar_comando(com);
      com.destruir();
  }

  // Encerrando execução do programa
  escal.destruir();
  arq_entrada.close();

  // conclui registro de acesso
  return finalizaMemLog();
}