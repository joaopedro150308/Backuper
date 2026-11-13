#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "configs.h"
#include "backups/bakcups.h"


int criar_nome_pasta(char *retorno)
{
    char nome[SUB_PASTAS_BACKUPS_NOME_TAM_MAX];
    struct tm *data;

    time_t t;
    t = time(NULL);

    data = localtime(&t);

    sprintf(nome, "%d-%d-%d_%d-%d", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900, data->tm_hour, data->tm_min);
    strcpy(retorno, nome);
    return 0;
}


int criar_pasta_para_backup(const char *pasta_nome)
{
    char backups_caminho[PATH_MAX];
    char sub_pasta[PATH_MAX];

    // Conseguindo caminho para a pasta Backups
    FILE *fptr = fopen(DATA_BACKUPS_PATH, "r");
    if(fptr == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fgets(backups_caminho, PATH_MAX, fptr);
    backups_caminho[strcspn(backups_caminho, "\n")] = '\0';
    fclose(fptr);

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