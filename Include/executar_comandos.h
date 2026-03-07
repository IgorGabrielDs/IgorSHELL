#ifndef EXECUTAR_COMANDOS_H
#define EXECUTAR_COMANDOS_H

#include <sys/types.h>

pid_t executar_comandos(char **palavras);
void tratar_style(char **palavras);
void executar_cd(char **palavras);

#endif