#include <stdio.h>

#include "configs.h"
#include "docs/docs.h"


int main()
{
    char caminho[CAMINHOS_TAM_MAX];
    ler_doc_path(caminho);

    printf("%s", caminho);

    return 0;
}