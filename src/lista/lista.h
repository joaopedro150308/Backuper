#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

#define INIT_CAP 2
#define RAZAO_GEO_REALLOC 2

// Lista de caminhos

typedef struct {
    char **caminhos; // Uma matriz de caracteres, ou vetor de strings.
    int cap; // Indica o o número máximo de espaços da lista no momento.
    int tam; // Indica o número de elementos presentes na lista.

} ListaCam;

/* 
Função responsável por inicializar uma lista com seus campos: capacidade inicial, tamanho inicial e alocar um array de strings.
*/
ListaCam lista_init();


/***********************************
    Funções próprias da lista
***********************************/

/*
Função que verifica se uma lsita está cheia. Retorna veidadeiro ou falso
*/
bool lista_cam_cheia(ListaCam lista);


/*
Limpa uma lista fazendo-a apontar para o primeiro espaço da lista
*/
void lista_cam_limpar(ListaCam *lista);


/*
Adiciona um caminho à lista de caminhos.

Parâmetros:
    - *lista: ponteiro para a lista de caminhos ao qual irá adicionar o caminho
    - *cam: string caminho que será adicionado à lista
*/
void lista_cam_add(ListaCam *lista, const char *cam);


/*
Aumenta a capacidade da lista

Parâmetros: 
    - ponteiro para a lista que será reallocada
*/
void lista_cam_realloc(ListaCam *lista);


/*
Função responsável por liberar a matriz de char i.e. o ponteiro dinâmico de caminhos.
*/
void lista_cam_free(ListaCam *lista);


#endif