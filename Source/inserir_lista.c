#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void inserir_lista(Node **head, char *texto){
    Node *novo = (Node*)malloc(sizeof(Node));
    if(novo == NULL){
        return;
    }

    strcpy(novo->texto, texto);
    novo->proximo = NULL;

    if(*head == NULL){
        *head = novo;
        return;
    }

    Node *atual = *head;
    while (atual->proximo != NULL){
        atual = atual->proximo;
    }
    atual->proximo = novo;
}