#ifndef DOCS_H
#define DOCS_H

// Esse caminho funciona, pois, no Makefile, configs/ está na lista de diretórios para Include.
#include "configs.h"


/*
Função que lê do usuário um caminho para um document (é apenas um exemplo :p)
*/
void ler_doc_path(char *retorno);

/*
Função que, dado o nome de um documento, cria um caminho para um documento de mesmo nome mas situado no caminho passado em "dest". O caminho criado é retornado como ponteiro com memória allocada. É necessário liberá-lo após o uso.
*/
char  *criar_dest_path(const char *doc_name, const char *dest);

#endif