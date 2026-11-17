#include <stdio.h>
#include <windows.h>

#include "configs.h"
#include "uteis/uteis.h"


int pasta_data_setup()
{
    if(pasta_existe(DATA_DIR_PATH))
    {
        printf("Pasta %s encontrada.\n", DATA_DIR_PATH);
    }
    else
    {
        // Tentando cria-la
        if(CreateDirectoryA(DATA_DIR_PATH, NULL))
        {
            printf("Sucesso ao criar pasta %s.\n", DATA_DIR_PATH);
        }
        else
        {
            printf("Erro ao criar pasta %s.\n", DATA_DIR_PATH);
            return 1;
        }
    }

    // Depois de criá-la, verifica também seus subdiretórios.
    char sub_dirs[][MAX_PATH] = {
        DATA_CAMINHOS_DIR_PATH
    };

    int quant_sub_dirs = sizeof(sub_dirs) / MAX_PATH;

    for(int i = 0; i < quant_sub_dirs; i++)
    {
        if(!pasta_existe(sub_dirs[i]))
        {
            if(CreateDirectoryA(sub_dirs[i], NULL))
            {
                printf("Sub diretório criado com sucesso em: %s.\n", sub_dirs[i]);
            }
        }
    }

    return 0;
}