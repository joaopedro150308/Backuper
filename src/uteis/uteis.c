#include <stdio.h>
#include <string.h>

#include "configs.h"







void limpar_cmd()
{
    // Usa sequeências de escape
    printf("\033c");
}


/*********************************
        Funções de i/o
*********************************/

int ler_inteiro(const char *msg)
{
    char buff[INPUT_CHAR_BUFF_MAX];
    int num;

    printf("%s", msg);
    fgets(buff, INPUT_CHAR_BUFF_MAX, stdin);
    sscanf(buff, "%d", &num);

    return num;
}


void ler_string(const char *msg, char *retorno)
{
    char buff[INPUT_CHAR_BUFF_MAX];

    printf("%s", msg);
    fgets(buff, INPUT_CHAR_BUFF_MAX, stdin);
    buff[strcspn(buff, "\n")] = '\0';

    strcpy(retorno, buff);
}