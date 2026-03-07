#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "main.h"

void ler_arquivo(int argc, char *argv[]){
    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL){
        printf("\x1b[1mIgds \x1b[32m%s\x1b[0m> Erro ao abrir arquivo \"%s\"\n", style, argv[1]);
        return;
    }

    char aux[200];

    while (fgets(aux, sizeof(aux), arquivo) != NULL){
        if (strcmp(aux, "\n") == 0){
            continue;
        }

        aux[strcspn(aux, "\n")] = '\0';

        if (strcmp(aux, "") == 0){
            continue;
        }

        printf("%s\n", aux);
        input_linha(aux);
    }

    printf("\n");
    fclose(arquivo);
}