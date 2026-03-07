CC = gcc
CFLAGS = -IInclude
OBJ = Objects/main.o Objects/arquivo.o Objects/inserir_lista.o Objects/input.o Objects/executar_comandos.o

igds: $(OBJ)
	$(CC) $(OBJ) -o igds

Objects/main.o: Source/main.c
	$(CC) $(CFLAGS) -c Source/main.c -o Objects/main.o

Objects/inserir_lista.o: Source/inserir_lista.c
	$(CC) $(CFLAGS) -c Source/inserir_lista.c -o Objects/inserir_lista.o

Objects/arquivo.o: Source/arquivo.c
	$(CC) $(CFLAGS) -c Source/arquivo.c -o Objects/arquivo.o

Objects/input.o: Source/input.c
	$(CC) $(CFLAGS) -c Source/input.c -o Objects/input.o

Objects/executar_comandos.o: Source/executar_comandos.c
	$(CC) $(CFLAGS) -c Source/executar_comandos.c -o Objects/executar_comandos.o

clean:
	rm -f Objects/*.o igds
