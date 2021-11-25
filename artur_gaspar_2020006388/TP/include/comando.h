#ifndef COMANDO
#define COMANDO

#include <iostream>
#include <string>
#include <fstream>

class Comando{
    public:
        Comando(std::string arq_saida);
        void executar();
        friend std::istream& operator >> (std::istream& is, Comando& com);

};


#endif