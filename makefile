igds: Objects/main.o 
	gcc Objects/main.o -o igds

Objects/main.o: Source/main.c Source/ler_arquivo.c Source/inserir_lista.c
	gcc -c Source/main.c -o Objects/main.o

Objects/inserir_lista.o: Source/inserir_lista Source/lista.h
