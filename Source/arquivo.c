#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "input.h"
#include <string.h>


void ler_arquivo(int argc, char *argv[]){
    for(int i=1;i<argc;i++){
        Node *frases = NULL;
        Node *palavras = NULL;

        FILE *arquivo = fopen(argv[i], "r");
        
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo %s\n", argv[i]);
            continue;
        }   
        char aux[100];
        while(fgets(aux, sizeof(aux), arquivo) != NULL){
            if(strcmp(aux, "\n") == 0) {
                continue;
            }else{
                inserir_lista(&frases, aux);
                char copia[100];
                
                strcpy(copia, aux);

                char *modificado = strtok(copia, " \n");
                while(modificado != NULL){
                    inserir_lista(&palavras, modificado);
                    modificado = strtok(NULL, " \n");
                }
            }
        }
        
        //input(frases, palavras);
        fclose(arquivo);
    }
}