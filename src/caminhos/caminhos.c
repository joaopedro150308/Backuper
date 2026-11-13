#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "configs.h"
#include "lista/lista.h"
#include "caminhos/caminhos.h"



/************************************
    Funções específicas de docs.c
************************************/


/************************************
    Funções que serão compartilhadas
    (estão também no .h)
************************************/

/*
Exemplo de função que seria distribuída com o .h, pois sua declaração está lá e sua descrição/implementação aqui.
*/
bool ler_doc_path(const char *msg, char *retorno)
{
    char buff[CAMINHOS_TAM_MAX];

    printf("%s", msg);
    fgets(buff, CAMINHOS_TAM_MAX, stdin);
    buff[strcspn(buff, "\n")] = '\0';

    // Verificando se o caminho é válido
    bool valido = false;
    if (access(buff, F_OK) == 0)
    {
        valido = true;
    }
    else
    {
        valido = false;
    }

    strcpy(retorno, buff);
    return valido;
}


void registrar_caminhos(ListaCam *lista)
{
    FILE *fptr = fopen(DATA_CAMINHOS_CAMINHOS_PATH, "a");
    if(!fptr)
    {
        printf("Não foi possível abrir o arquivo de caminhos.\n");
        return;
    }

    for(int j = 0; j < lista->tam; j++)
    {
        fprintf(fptr, "%s\n", lista->caminhos[j]);
    }
    fclose(fptr);
}


char  *criar_dest_path(const char *doc_name, const char *dest_dir)
{
    char *buff = malloc(CAMINHOS_TAM_MAX);
    if(!buff)
    {
        printf("Erro ao criar caminho de destino.\n");
        exit(1);
    }

    sprintf(buff, "%s\\%s", dest_dir, doc_name);

    return buff;
}
