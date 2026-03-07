#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"
#include "executar_comandos.h"
#include "input.h"
#include "arquivo.h"

char **input_palavra(char *comando){
    char **palavras = NULL;
    int qtd = 0;

    char copia[200];
    strcpy(copia, comando);

    char *token = strtok(copia, " \t\n");

    while (token != NULL){
        inserir_lista(&palavras, &qtd, token);
        token = strtok(NULL, " \t\n");
    }

    return palavras;
}

void input_linha(char *linha){
    char copia[200];
    strcpy(copia, linha);

    pid_t processos[100];
    int qtd_processos = 0;

    char *comando = strtok(copia, ";");

    while (comando != NULL){
        char **palavras = input_palavra(comando);

        if (palavras != NULL){
            pid_t pid = input_codigo(palavras);

            if (pid > 0){
                if (strcmp(style, "seq") == 0){
                    waitpid(pid, NULL, 0);
                }
                else if (strcmp(style, "par") == 0){
                    processos[qtd_processos] = pid;
                    qtd_processos++;
                }
            }

            free_lista(palavras);
        }

        comando = strtok(NULL, ";");
    }

    if (strcmp(style, "par") == 0){
        for (int i = 0; i < qtd_processos; i++){
            waitpid(processos[i], NULL, 0);
        }
    }
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