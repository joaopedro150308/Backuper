#ifndef DOCS_H
#define DOCS_H

#include <stdbool.h>

// Esse caminho funciona, pois, no Makefile, configs/ está na lista de diretórios para Include.
#include "configs.h"
#include "lista/lista.h"


/*
Função que lê do usuário um caminho para um documento. Retorna verdadeiro caso o caminho lido seja válido (caso o arquivo ou diretório exista), caso contrário retorna falso. O caminho, uma vez válido, é copiado para "retorno". 
*/
bool ler_doc_path(const char *msg, char *retorno);

/*
-> Registra em um arquivo de texto os caminhos armazenados em uma lista de caminhos

:param lista: A lista com os caminhos
*/
void registrar_caminhos(ListaCam *lista);


/*
Função que, dado o nome de um documento, cria um caminho para um documento de mesmo nome mas situado no caminho passado em "dest". O caminho criado é retornado como ponteiro com memória allocada. É necessário liberá-lo após o uso.
*/
char  *criar_dest_path(const char *doc_name, const char *dest);

#endif