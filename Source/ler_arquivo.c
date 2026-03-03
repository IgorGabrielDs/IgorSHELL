#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "inserir_lista.h"

void ler_arquivo(int argc, char *argv[], FILE *arquivo, Node **head){
    for(int i=1;i<argc;i++){
        arquivo = fopen(argv[i], "r");
        char aux[100];
        while(fscanf(arquivo, "%*s", aux) == 1){
            printf("%s\n", aux);
        }
    }
}