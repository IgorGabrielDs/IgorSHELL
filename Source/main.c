#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler_arquivo.h"

int main(int argc, char *argv[]){
    while(1){
        if(argc > 1){
            FILE *arquivo;
            Node *head = NULL;
            ler_arquivo(argc, argv, arquivo, &head);
            //funçao input
        }
        //digitar texto
        //funçao input
        return 0;
    }
    return 0;
}