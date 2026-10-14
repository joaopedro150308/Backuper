#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "configs.h"
#include "copia/copia.h"
#include "docs/docs.h"


int main()
{
    char dest[CAMINHOS_TAM_MAX] = "C:\\Users\\joaop\\Desktop\\Backups";
    char caminho[CAMINHOS_TAM_MAX];

    ler_doc_path(caminho);

    bool sucesso = copy_doc(caminho, dest);

    if(sucesso)
        printf("\nCopia bem sucedida\n");
        
    return 0;
}
