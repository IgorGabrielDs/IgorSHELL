#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void ler_arquivo(int argc, char *argv[]){
    for(int i=1;i<argc;i++){
        Node *head = NULL;
        FILE *arquivo = fopen(argv[i], "r");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo %s\n", argv[i]);
            continue;
        }   
        char aux[100];
        while(fgets(aux, sizeof(aux), arquivo) != NULL){
            inserir_lista(&head, aux);
        }
        //input
        fclose(arquivo);
    }
}