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
#include "jobs.h"

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
    if (strcmp(palavras[0], "help") == 0){
        printf("\x1b[1;36m\nComandos disponiveis no IGDSshell:\x1b[0m\n\n"
        "\x1b[1;33mhelp\x1b[0m               - mostra esta lista de comandos\n"
        "\x1b[1;33mstyle sequential\x1b[0m   - define execucao sequencial\n"
        "\x1b[1;33mstyle parallel\x1b[0m     - define execucao paralela\n"
        "\x1b[1;33mcd <diretorio>\x1b[0m     - muda o diretorio atual\n"
        "\x1b[1;33mexit\x1b[0m               - encerra o shell\n"
        "\x1b[1;33mfg <id>\x1b[0m            - traz um job do background para foreground\n"
        "\x1b[1;33m<comando> &\x1b[0m        - executa comando em background\n"
        "\x1b[1;33m<comando1> ; <comando2>\x1b[0m - executa multiplos comandos na mesma linha\n"
        "\x1b[1;33m<comando1> | <comando2>\x1b[0m - executa comandos com pipe\n"
        "\x1b[1;33m<comando> > arquivo\x1b[0m  - redireciona saida para arquivo\n"
        "\x1b[1;33m<comando> >> arquivo\x1b[0m - adiciona saida ao final do arquivo\n"
        "\x1b[1;33m<comando> < arquivo\x1b[0m  - usa arquivo como entrada\n"
        "\x1b[1;33m<comandos Linux>\x1b[0m     - executa comandos externos via execvp\n\n"
        );
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

    if (strcmp(palavras[0], "fg") == 0){
        if (palavras[1] == NULL){
            printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mfg: argumento faltando\x1b[0m\n", style);
        }
        else{
            trazer_fg(atoi(palavras[1]));
        }
        return -1;
    }

    if (strcmp(palavras[0], "exit") == 0){
        exit(0);
    }

    return executar_comandos(palavras);
}

void remover_espacos_finais(char *texto){
    int i = strlen(texto) - 1;

    while (i >= 0 && (texto[i] == ' ' || texto[i] == '\t' || texto[i] == '\n')){
        texto[i] = '\0';
        i--;
    }
}

void input_linha(char *linha){
    char copia_linha[200];
    strcpy(copia_linha, linha);

    pid_t pids[100];
    int qtd_pids = 0;

    char *contexto_comando;
    char *comando_atual = strtok_r(copia_linha, ";", &contexto_comando);

    while (comando_atual != NULL){
        verificar_jobs();

        remover_espacos_finais(comando_atual);

        if (strchr(comando_atual, '|') != NULL){
            executar_pipe(comando_atual);
            comando_atual = strtok_r(NULL, ";", &contexto_comando);
            continue;
        }

        if (strchr(comando_atual, '>') != NULL || strchr(comando_atual, '<') != NULL){
            executar_redirecionamento(comando_atual);
            comando_atual = strtok_r(NULL, ";", &contexto_comando);
            continue;
        }

        int background = 0;
        int tam = strlen(comando_atual);

        if (tam > 0 && comando_atual[tam - 1] == '&'){
            background = 1;
            comando_atual[tam - 1] = '\0';
            remover_espacos_finais(comando_atual);
        }

        char **palavras = input_palavra(comando_atual);

        if (palavras != NULL && palavras[0] != NULL){
            pid_t pid = input_codigo(palavras);

            if (pid > 0){
                if (background){
                    adicionar_job(pid, comando_atual);
                }
                else if (strcmp(style, "seq") == 0){
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