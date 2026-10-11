#include <stdio.h>
#include <string.h>

#include "configs.h"
#include "docs/docs.h"



/************************************
    Funções específicas de docs.c
************************************/

/*
Exemplo de função que ficará disponível apenas no .c, não será distribuída ao incluir "docs.h".
*/
void formatar_caminho(char* alvo)
{
    printf("Formatando %s...\n", alvo);
    printf("Formatado!\n");
}





/************************************
    Funções que serão compartilhadas
    (estão também no .h)
************************************/

/*
Exemplo de função que seria distribuída com o .h, pois sua declaração está lá e sua descrição/implementação aqui.
*/
void ler_doc_path(char *retorno)
{
    char buff[CAMINHOS_TAM_MAX];

    printf("Insira o caminho para um documento: ");
    fgets(buff, CAMINHOS_TAM_MAX, stdin);
    buff[strcspn(buff, "\n")] = '\0';

    formatar_caminho(buff);

    strcpy(retorno, buff);
    printf("Caminho retornado!\n");
}