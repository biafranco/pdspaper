## -c <arquivo>         compilar
## -o <arquivo>         direciona a saida
## -J <diretorio>       direciona .mod para o diretorio
## -I <diretorio>       busca modulos no diretorio

## *.o      todos os arquivos .o (ou qualquer outra extensão) 
## %.o      igual *, mas para alvos e dependencias com a extensão especificada
## $<       primeira dependencia
## $@       o alvo

CC := g++
I = -I include

MAIN := ./src/main.cpp
DATA := ./src/database.cpp
INC := ./include/database.h
BLD := ./build

OBJ = $(BLD)/database.o $(BLD)/main.o

all: programa

programa: $(OBJ)
	$(CC) $(OBJ) -o tp_execution


$(BLD)/database.o:	$(DATA) $(INC)
	$(CC) $(I) -c $< -o $@

$(BLD)/main.o:	$(MAIN)
	$(CC) $(I) -c $^ -o $@ 

## É algo parecido com isso
## PRECISA TESTAR