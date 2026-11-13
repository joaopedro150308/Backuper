#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "configs.h"
#include "copia/copia.h"
#include "caminhos/caminhos.h"
#include "uteis/uteis.h"
#include "lista/lista.h"

/* Protótipos de telas */

int pagina_inicial(void);
void adicionar_caminhos(void);
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
            adicionar_caminhos();
            break;

        case 2:
            // pagina2();
            break;

        case 0:
            printf("\nENCERRANDO PROGRAMA\n\n");
            break;

        default:
            printf("\nOPÇÃO INVÁLIDA\n\n");
            aviso("ERRO: Valor fora de alcance. Digite uma opção válida.\n");
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


void adicionar_caminhos(void)
{
    ListaCam lista = lista_init(); // Uma lista de caminhos.
    
    int i;
    char caminho[CAMINHOS_TAM_MAX], msg[64];

    // Lendo caminhos
    for (i = 0;; i++)
    {
        limpar_cmd();
        printf("\nDIGITE ABAIXO OS CAMINHOS DAS PASTAS QUE DESEJA FAZER BACKUP\nPARA VOLTAR AO MENU PRINCIPAL DIGITE : 0\n\n");

        // Lendo caminho
        sprintf(msg, "Digite o %dº caminho: ", i+1);

        // Se o caminho for inválido,
        if (!ler_doc_path(msg, caminho))
        {
            // Verificando se é o flag
            if (caminho[0] == '0')
                break;
            else
            {
                aviso("\nErro ao ler caminhos. Caminho inválido. Tente novamente.\n");
                i--; continue;
            }
        }
        else
        {
            // Adicionando caminho
            lista_cam_add(&lista, caminho);
        }
    }
        
    // Registrando caminhos lidos (poderia ser uma função separada)
    registrar_caminhos(&lista);
    lista_cam_free(&lista);
}
