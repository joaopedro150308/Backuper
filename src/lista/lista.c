#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lista/lista.h"
#include "configs.h"


ListaCam lista_init()
{
    ListaCam lista;

    lista.cap = INIT_CAP;
    lista.tam = 0;

    lista.caminhos = calloc(lista.cap, sizeof(char*));
    if(!lista.caminhos)
    {
        printf("\nErro ao alocar linhas para a lista.\n");
        return lista;
    }

    return lista;
}


bool lista_cam_cheia(ListaCam *lista)
{
    return lista->cap == lista->tam;
}


void lista_cam_limpar(ListaCam *lista)
{
    lista->tam = 0;
}


void lista_cam_add(ListaCam *lista, const char *cam)
{
    char *novo_cam = malloc(CAMINHOS_TAM_MAX);
    if(!novo_cam)
    {
        printf("Erro ao adicionar novo caminho.\n");
        return;
    }

    strcpy(novo_cam, cam);
    // Adicionando
    if(lista_cam_cheia(lista))
    {
        lista_cam_realloc(lista);
    }
    lista->caminhos[lista->tam] = novo_cam;
    lista->tam = lista->tam + 1;
}


void lista_cam_realloc(ListaCam *lista)
{
    lista->cap = lista->cap * 2;
    
    char **novo_caminhos = realloc(lista->caminhos, lista->cap * sizeof(char*));
    if(!novo_caminhos)
    {
        printf("Erro ao reallocar novo_caminhos");
        lista->cap = lista->cap / 2;
        return;
    }
    lista->caminhos = novo_caminhos;
}


void lista_cam_free(ListaCam *lista)
{
    for(int i = 0; i < lista->tam; i++)
    {
        free(lista->caminhos[i]);
    }
    free(lista->caminhos);
}
