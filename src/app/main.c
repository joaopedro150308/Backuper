#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "configs.h"
#include "copia/copia.h"
#include "docs/docs.h"
#include "uteis/uteis.h"
#include "lista/lista.h"

/* Protótipos de telas */

int pagina_inicial(void);
void pagina1(void);
void pagina2(void);


int main()
{
    // char dest[CAMINHOS_TAM_MAX] = "C:\\Users\\joaop\\Desktop\\Backups";
    // char caminho[CAMINHOS_TAM_MAX];

    // ler_doc_path(caminho);

    // bool sucesso = copy_doc(caminho, dest);

    // if(sucesso)
    //     printf("\nCopia bem sucedida\n");
    
    limpar_cmd();
    int n = -1;

    while (n != 0)
    {
        n = pagina_inicial();

        switch (n)
        {
        case 1:
            pagina1();
            break;

        case 2:
            // pagina2();
            break;

        case 0:
            printf("\nENCERRANDO PROGRAMA\n\n");
            break;

        default:
            printf("\nOPÇÃO INVÁLIDA\n\n");
            break;
        }
    }




    return 0;
}


int pagina_inicial(void)
{
    int n;
    limpar_cmd();

    printf("\n\nGUIA DE COMANDOS:\n\n0 -> FINALIZAR O PROGRAMA\n1 -> ADICIONAR CAMINHOS/DOCUMENTOS\n2 -> FAZER BACKUP\n\n\n--------------------------------------------------\n\n");
    n = ler_inteiro("Sua opção: ");

    return n;
}


void pagina1(void)
{
    ListaCam lista = lista_init(); // Uma lista de caminhos.
    
    limpar_cmd();
    printf("\nDIGITE ABAIXO OS CAMINHOS DAS PASTAS QUE DESEJA FAZER BACKUP\nPARA VOLTAR AO MENU PRINCIPAL DIGITE : 0\n\n");

    int i;
    char caminho[CAMINHOS_TAM_MAX], msg[64];

    // Lendo caminhos
    for (i = 0;; i++)
    {
        // Lendo caminho
        sprintf(msg, "Digite o %dº caminho: ", i+1);
        ler_string(msg, caminho);

        // Verificando flag
        if (caminho[0] == '0')
            break;

        // Adicionando caminho
        if(lista_cam_cheia(lista))
        {
            lista_cam_realloc(&lista);
        }
        lista_cam_add(&lista, caminho);
    }

    // Registrando caminhos (poderia ser uma função separada)

        // Registrando quantidade de caminhos lidos
    FILE *fptr = fopen(DATA_CAMINHOS_CONTAGEM_PATH, "w");
    if (fptr == NULL)
    {
        printf("\nERRO: Não foi possível localizar o arquivo de contagem.\n");
        return;
    }

    fprintf(fptr, "%d", lista.tam);
    fclose(fptr);

        // Registrando caminhos lidos (poderia ser uma função separada)
    fptr = fopen(DATA_CAMINHOS_CAMINHOS_PATH, "w");
    if(!fptr)
    {
        printf("Não foi possível abrir o arquivo de caminhos.\n");
        return;
    }

    for(int j = 0; j < lista.tam; j++)
    {
        fprintf(fptr, "%s\n", lista.caminhos[j]);
    }
    fclose(fptr);

    lista_cam_free(&lista);
}

