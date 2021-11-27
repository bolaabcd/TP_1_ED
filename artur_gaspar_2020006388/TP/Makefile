#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa escalonador
# Autor		: Artur Gaspar da Silva (artur.gaspar@dcc.ufmg.br)
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		    : make clean - remove objetos e executável
#---------------------------------------------------------------------

# Diretórios
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# Opções do compilador
CC = g++
CFLAGS = -Wall -c -I$(INCLUDE_FOLDER)
LIBS = -lm

# Arquivos
TARGET = $(BIN_FOLDER)/escalonador
HDR_FILES = $(INCLUDE_FOLDER)/comando.h  $(INCLUDE_FOLDER)/escalona.h $(INCLUDE_FOLDER)/fila_hosts.h $(INCLUDE_FOLDER)/host.h $(INCLUDE_FOLDER)/memlog.h $(INCLUDE_FOLDER)/msgassert.h $(INCLUDE_FOLDER)/url.h
OBJ_FILES = $(OBJ_FOLDER)/comando.o $(OBJ_FOLDER)/escalona.o $(OBJ_FOLDER)/fila_hosts.o $(OBJ_FOLDER)/host.o $(OBJ_FOLDER)/memlog.o $(OBJ_FOLDER)/url.o

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $(TARGET) $(LIBS) $(OBJ_FILES)

$(OBJ_FOLDER)/comando.o: $(HDR_FILES) $(SRC_FOLDER)/comando.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/comando.o $(SRC_FOLDER)/comando.cpp 

$(OBJ_FOLDER)/escalona.o: $(HDR_FILES) $(SRC_FOLDER)/escalona.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/escalona.o $(SRC_FOLDER)/escalona.cpp 

$(OBJ_FOLDER)/fila_hosts.o: $(HDR_FILES) $(SRC_FOLDER)/fila_hosts.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/fila_hosts.o $(SRC_FOLDER)/fila_hosts.cpp 

$(OBJ_FOLDER)/host.o: $(HDR_FILES) $(SRC_FOLDER)/host.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/host.o $(SRC_FOLDER)/host.cpp 

$(OBJ_FOLDER)/memlog.o: $(HDR_FILES) $(SRC_FOLDER)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/memlog.o $(SRC_FOLDER)/memlog.cpp 
	
$(OBJ_FOLDER)/url.o: $(HDR_FILES) $(SRC_FOLDER)/url.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/url.o $(SRC_FOLDER)/url.cpp 

clean:
	rm $(TARGET) $(OBJ_FILES) 
