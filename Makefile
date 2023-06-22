
CC = g++
LIBS = -lm
SRC = src
OBJ = build
INC = include
BIN = bin

OBJS = $(OBJ)/database.o $(OBJ)/main.o

HDRS = $(INC)/database.h

CFLAGS = -Wall -c -I$(INC)

all: programa

programa: $(OBJS)
	$(CC) $(OBJS) -o $(BIN)/tp_execution $(LIBS)

$(OBJ)/database.o: $(HDRS) $(SRC)/database.cpp 
	$(CC) $(CFLAGS) -o $(OBJ)/database.o $(SRC)/database.cpp

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp 
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
## Função para Linux:
	rm -f $(OBJ)/*.o $(BIN)/tp_execution

## Função para Windows:
##	del /Q $(OBJ)\*.o 
##	del /Q $(BIN)\tp_execution.exe