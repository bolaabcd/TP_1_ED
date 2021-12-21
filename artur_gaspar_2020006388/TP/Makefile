#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa escalonar
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
TARGET = $(BIN_FOLDER)/escalonar
TARGET1 = $(BIN_FOLDER)/desafio1
TARGET2 = $(BIN_FOLDER)/desafio2
HDR_FILES = $(INCLUDE_FOLDER)/comando.h $(INCLUDE_FOLDER)/fila_hosts_desafio2.h $(INCLUDE_FOLDER)/escalonador.h $(INCLUDE_FOLDER)/fila_hosts.h $(INCLUDE_FOLDER)/host.h $(INCLUDE_FOLDER)/memlog.h $(INCLUDE_FOLDER)/msgassert.h $(INCLUDE_FOLDER)/url.h
OBJ_FILES = $(OBJ_FOLDER)/comando.o $(OBJ_FOLDER)/escalonador.o $(OBJ_FOLDER)/fila_hosts.o $(OBJ_FOLDER)/host.o $(OBJ_FOLDER)/escalonar.o $(OBJ_FOLDER)/memlog.o $(OBJ_FOLDER)/url.o
OBJ_FILES1 = $(OBJ_FOLDER)/comando.o $(OBJ_FOLDER)/escalonador_desafio1.o $(OBJ_FOLDER)/fila_hosts.o $(OBJ_FOLDER)/host.o $(OBJ_FOLDER)/escalonar.o $(OBJ_FOLDER)/memlog.o $(OBJ_FOLDER)/url.o
OBJ_FILES2 = $(OBJ_FOLDER)/comando.o $(OBJ_FOLDER)/escalonador_desafio2.o $(OBJ_FOLDER)/fila_hosts_desafio2.o $(OBJ_FOLDER)/host.o $(OBJ_FOLDER)/escalonar.o $(OBJ_FOLDER)/memlog.o $(OBJ_FOLDER)/url.o


all: $(TARGET) $(TARGET1) $(TARGET2)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $(TARGET) $(LIBS) $(OBJ_FILES)

$(TARGET1): $(OBJ_FILES1)
	$(CC) -o $(TARGET1) $(LIBS) $(OBJ_FILES1)

$(TARGET2): $(OBJ_FILES2)
	$(CC) -o $(TARGET2) $(LIBS) $(OBJ_FILES2)

$(OBJ_FOLDER)/comando.o: $(HDR_FILES) $(SRC_FOLDER)/comando.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/comando.o $(SRC_FOLDER)/comando.cpp 

$(OBJ_FOLDER)/escalonador.o: $(HDR_FILES) $(SRC_FOLDER)/escalonador.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/escalonador.o $(SRC_FOLDER)/escalonador.cpp 

$(OBJ_FOLDER)/escalonador_desafio1.o: $(HDR_FILES) $(SRC_FOLDER)/escalonador_desafio1.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/escalonador_desafio1.o $(SRC_FOLDER)/escalonador_desafio1.cpp 

$(OBJ_FOLDER)/escalonador_desafio2.o: $(HDR_FILES) $(SRC_FOLDER)/escalonador_desafio2.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/escalonador_desafio2.o $(SRC_FOLDER)/escalonador_desafio2.cpp 

$(OBJ_FOLDER)/fila_hosts.o: $(HDR_FILES) $(SRC_FOLDER)/fila_hosts.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/fila_hosts.o $(SRC_FOLDER)/fila_hosts.cpp 

$(OBJ_FOLDER)/fila_hosts_desafio2.o: $(HDR_FILES) $(SRC_FOLDER)/fila_hosts_desafio2.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/fila_hosts_desafio2.o $(SRC_FOLDER)/fila_hosts_desafio2.cpp 

$(OBJ_FOLDER)/host.o: $(HDR_FILES) $(SRC_FOLDER)/host.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/host.o $(SRC_FOLDER)/host.cpp 

$(OBJ_FOLDER)/escalonar.o: $(HDR_FILES) $(SRC_FOLDER)/escalonar.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/escalonar.o $(SRC_FOLDER)/escalonar.cpp 

$(OBJ_FOLDER)/memlog.o: $(HDR_FILES) $(SRC_FOLDER)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/memlog.o $(SRC_FOLDER)/memlog.cpp 
	
$(OBJ_FOLDER)/url.o: $(HDR_FILES) $(SRC_FOLDER)/url.cpp
	$(CC) $(CFLAGS) -o $(OBJ_FOLDER)/url.o $(SRC_FOLDER)/url.cpp 

clean:
	rm $(TARGET) $(TARGET1) $(TARGET2) $(OBJ_FILES) $(OBJ_FOLDER)/escalonador_desafio1.o $(OBJ_FOLDER)/escalonador_desafio2.o $(OBJ_FOLDER)/fila_hosts_desafio2.o
