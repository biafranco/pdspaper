## -c <arquivo>         compilar
## -o <arquivo>         direciona a saida
## -J <diretorio>       direciona .mod para o diretorio
## -I <diretorio>       busca modulos no diretorio

## *.o      todos os arquivos .o (ou qualquer outra extensão) 
## %.o      igual *, mas para alvos e dependencias com a extensão especificada
## $<       primeira dependencia
## $@       o alvo

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/database.o $(OBJ)/main.o

HDRS = $(INC)/database.h

CFLAGS = -pg -Wall -c -I$(INC)

all: programa

programa: $(OBJ)
	$(CC) $(OBJ) -o tp_execution

$(OBJ)/database.o: $(HDRS) $(SRC)/database.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/database.o $(SRC)/database.cpp

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
rm $(OBJ)/*.o $(BIN)/tp0.exe

## É algo parecido com isso
## PRECISA TESTAR 
## tbm não testei


