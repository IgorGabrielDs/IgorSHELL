#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void inserir_lista(char ***lista, int *qtd, char *texto){
    
    char **temp = realloc(*lista, sizeof(char*) * (*qtd + 2));
    if (temp == NULL){
        return;
    }

    *lista = temp;

    (*lista)[*qtd] = malloc(strlen(texto) + 1);
    if ((*lista)[*qtd] == NULL){
        return;
    }

    strcpy((*lista)[*qtd], texto);
    (*qtd)++;

    (*lista)[*qtd] = NULL;
}

void free_lista(char **lista){
    if (lista == NULL){
        return;
    }
    for (int i = 0; lista[i] != NULL; i++){
        free(lista[i]);
    }
    free(lista);
}