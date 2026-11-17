#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "configs.h"
#include "uteis/uteis.h"




/*********************************
        Funções de i/o
*********************************/


int ler_inteiro(const char *msg)
{
    char buff[INPUT_CHAR_BUFF_MAX];
    char *endPtr;
    int num;

    do
    {
        printf("%s", msg);
        fgets(buff, INPUT_CHAR_BUFF_MAX, stdin);
        num = strtol(buff, &endPtr, 10);

        if (endPtr == buff)
        {
            aviso("\nERRO: valor inválido. Digite um número inteiro válido.\n");
        }
    } while (endPtr == buff);
    
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


void limpar_cmd()
{
    // Usa sequeências de escape
    printf("\033c");
}


void aviso(const char *msg)
{
    char buff[10];
    printf("%s", msg);
    ler_string("Pressione ENTER para continuar.\n", buff);
}

/*************************************
        Funções para arquvos
*************************************/

int pasta_existe(const char *caminho)
{
    DWORD atributos = GetFileAttributes(caminho);

    return (atributos != INVALID_FILE_ATTRIBUTES && atributos & FILE_ATTRIBUTE_DIRECTORY);
}