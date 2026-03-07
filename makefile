all = Objects/main.o Objects/arquivo.o Objects/inserir_lista.o Objects/input.o Objects/executar.o

igds: $(all)
	gcc -IInclude $(all) -o igds

Objects/main.o: Source/main.c
	gcc -IInclude -c Source/main.c -o Objects/main.o

Objects/inserir_lista.o: Source/inserir_lista.c
	gcc -IInclude -c Source/inserir_lista.c -o Objects/inserir_lista.o

Objects/arquivo.o: Source/arquivo.c
	gcc -IInclude -c Source/arquivo.c -o Objects/arquivo.o

Objects/input.o: Source/input.c
	gcc -IInclude -c Source/input.c -o Objects/input.o

Objects/executar.o: Source/executar.c
	gcc -IInclude -c Source/executar.c -o Objects/executar.o

