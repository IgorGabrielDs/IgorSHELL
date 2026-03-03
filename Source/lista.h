#ifndef LISTA_H
#define LISTA_H

typedef struct node
{
    char texto[100];
    struct node *proximo;
}Node;

void inserir_lista(Node **head, char *texto);

#endif
