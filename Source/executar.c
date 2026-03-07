#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "main.h"
#include "executar.h"

pid_t executar_comandos(char **palavras){
    pid_t pid = fork();

    if (pid < 0){
        perror("fork");
        return -1;
    }

    if (pid == 0){
        execvp(palavras[0], palavras);
        perror("execvp");
        exit(1);
    }

    return pid;
}

void tratar_style(char **palavras){
    if (palavras[1] == NULL){
        printf("style: argumento faltando\n");
        return;
    }

    if (strcmp(palavras[1], "sequential") == 0){
        strcpy(style, "seq");
    }
    else if (strcmp(palavras[1], "parallel") == 0){
        strcpy(style, "par");
    }
    else{
        printf("style: modo invalido\n");
    }
}

void executar_cd(char **palavras){
    if (palavras[1] == NULL){
        printf("cd: argumento faltando\n");
        return;
    }

    if (chdir(palavras[1]) != 0){
        perror("cd");
    }
}