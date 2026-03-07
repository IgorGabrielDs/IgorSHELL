#ifndef INPUT_H
#define INPUT_H

#include <sys/types.h>

void input_linha(char *linha);
char **input_palavra(char *comando);
pid_t input_codigo(char **palavras);

#endif