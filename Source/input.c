#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"
#include "executar.h"
#include "input.h"
#include "arquivo.h"

char **input_palavra(char *comando){
    char **palavras = NULL;
    int qtd_palavras = 0;   

    char copia[200];
    strcpy(copia, comando);

    char *contexto_palavra;
    char *palavra_atual = strtok_r(copia, " \t\n", &contexto_palavra);

    while (palavra_atual != NULL){
        inserir_lista(&palavras, &qtd_palavras, palavra_atual);
        palavra_atual = strtok_r(NULL, " \t\n", &contexto_palavra);
    }

    return palavras;
}

pid_t input_codigo(char **palavras){
    if (palavras == NULL || palavras[0] == NULL){
        return -1;
    }

    if (strcmp(palavras[0], "style") == 0){
        tratar_style(palavras);
        return -1;
    }

    if (strcmp(palavras[0], "cd") == 0){
        executar_cd(palavras);
        return -1;
    }

    if (strcmp(palavras[0], "exit") == 0){
        exit(0);
    }

    return executar_comandos(palavras);
}



void input_linha(char *linha){
    char copia_linha[200];
    strcpy(copia_linha, linha);

    pid_t pids[100];
    int qtd_pids = 0;

    char *contexto_comando;
    char *comando_atual = strtok_r(copia_linha, ";", &contexto_comando);

    while (comando_atual != NULL){
        char **palavras = input_palavra(comando_atual);

        if (palavras != NULL && palavras[0] != NULL){
            pid_t pid = input_codigo(palavras);

            if (pid > 0){
                if (strcmp(style, "seq") == 0){
                    waitpid(pid, NULL, 0);
                }
                else if (strcmp(style, "par") == 0){
                    pids[qtd_pids] = pid;
                    qtd_pids++;
                }
            }
        }

        free_lista(palavras);
        comando_atual = strtok_r(NULL, ";", &contexto_comando);
    }

    if (strcmp(style, "par") == 0){
        for (int i = 0; i < qtd_pids; i++){
            waitpid(pids[i], NULL, 0);
        }
    }
}