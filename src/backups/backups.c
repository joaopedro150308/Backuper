#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "configs.h"
#include "uteis/uteis.h"
#include "backups/bakcups.h"


int pasta_backups_setup()
{
    if(!pasta_existe(BACKUPS_DIR_PATH))
    {
        printf("Pasta Backups não encontrada. Criando uma nova...\n");
        if(CreateDirectoryA(BACKUPS_DIR_PATH, NULL))
        {
            printf("Pasta Backups criada com sucesso.\n");
            return 0; // Sucesso.
        }
        else
        {
            printf("Erro ao criar pasta Backups.\n");
            return 1;
        }
    }
    else
    {
        printf("Pasta Backups já existe.\n");
        return 0;
    }
}


int criar_nome_pasta(char *retorno)
{
    char nome[SUB_PASTAS_BACKUPS_NOME_TAM_MAX];
    struct tm *data;

    time_t t;
    t = time(NULL);

    data = localtime(&t);

    sprintf(nome, "%2d-%2d-%4d_%2d-%2d", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900, data->tm_hour, data->tm_min);
    strcpy(retorno, nome);
    return 0;
}


int criar_pasta_para_backup(const char *pasta_nome)
{
    char backups_caminho[PATH_MAX] = {BACKUPS_DIR_PATH};
    char sub_pasta[PATH_MAX];


    // Montando caminho para a subpasta que será criada
    sprintf(sub_pasta, "%s\\%s", backups_caminho, pasta_nome);

    // Criando pasta
    if(CreateDirectoryA(sub_pasta, NULL))
    {
        printf("Sub pasta criada com sucesso.\n");
        return 0;
    }
    else
    {
        printf("Erro ao criar pasta. Código de erro: %ld", GetLastError());
        return 1;
    }
}