#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define T 150 // T ---> referente ao tamanho da str caminho

typedef struct
{
    char endereco[T];
} lista;

int n, i, qtd_enderecos, z, n_pasta; // n --> referencial às opções(VOLTAR, BACKUP, ADICIONAR ARQUIVO ...)
lista *caminhos, *temp;              //  --> str com o caminho das pastas que serão feitos os backups
FILE *fptr;

void pagina_inicial(void);
void pagina1(void);
void pagina2(void);

int main()
{
    system("cls");
    n = -1;

    while (n != 0)
    {
        pagina_inicial();
        scanf("%d%*c", &n);

        switch (n)
        {
        case 1:
            pagina1();
            break;

        case 2:
            pagina2();
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

void pagina_inicial(void)
{
    system("cls");

    printf("\n\nGUIA DE COMANDOS:\n\n0 -> FINALIZAR O PROGRAMA\n1 -> ADICIONAR CAMINHOS/DOCUMENTOS\n2 -> FAZER BACKUP\n\n\n--------------------------------------------------\n\n");
}

void pagina1(void)
{
    caminhos = (lista *)malloc(sizeof(lista));
    system("cls");
    printf("\nDIGITE ABAIXO OS CAMINHOS DAS PASTAS QUE DESEJA FAZER BACKUP\nPARA VOLTAR AO MENU PRINCIPAL DIGITE : 0\n\n");
    for (i = 0;; i++)
    {
        if (i > 0)
        {
            temp = (lista *)realloc(caminhos, sizeof(lista) * (i + 1));
            if (temp == NULL)
            {
                printf("\nFALHA AO ALOCAR MEMORIA\n\n");
                exit(1);
            }
            else
            {
                caminhos = temp;
            }
        }
        scanf("%s%*c", caminhos[i].endereco);
        if (caminhos[i].endereco[0] == '0')
            break;
    }
    qtd_enderecos = i;
    fptr = fopen("\\home\\heitor\\Documentos\\data\\contagem.txt", "wb");
    if (fptr == NULL)
    {
        system("mkdir \\home\\heitor\\Documentos\\data");
        fptr = fopen("\\home\\heitor\\Documentos\\data\\contagem.txt", "wb");
    }

    fwrite(&qtd_enderecos, sizeof(int), 1, fptr);
    fclose(fptr);
    fptr = fopen("\\home\\heitor\\Documentos\\data\\doc_origem.txt", "wb");

    fwrite(caminhos, sizeof(lista) * (qtd_enderecos + 1), 1, fptr);
    fclose(fptr);
}

void pagina2(void)
{
    FILE *ftemp;
    time_t tempo_atual;
    time(&tempo_atual);

    struct tm *data = localtime(&tempo_atual);
    int dia, mes, ano;
    dia = data->tm_mday;
    mes = data->tm_mon + 1;
    ano = data->tm_year + 1900;
    char backup_name[T];

    sprintf(backup_name, "mkdir \\home\\heitor\\Documentos\\data\\%d-%d-%d", dia, mes, ano);
    system(backup_name);

    system("cls");
    lista *ler_caminhosBin;
    printf("\nSELECIONE QUAIS PASTAS DESEJA SALVAR:\n\n0 --> VOLTAR AO MENU PRINCIPAL\n");
    fptr = fopen("\\home\\heitor\\Documentos\\data\\contagem.txt", "rb");
    if (fptr == NULL)
    {
        system("cls");
        printf("\nA PASTA DE CAMINHOS AINDA NAO FOI SALVA, RETORNE AO MENU PRINCIPAL E ADICIONE CAMINHOS/DOCUMENTOS\n\n--------ENTER PARA VOLTAR--------\n\n");
        scanf("%*c");
        return;
    }
    fread(&qtd_enderecos, sizeof(int), 1, fptr);
    fclose(fptr);
    ler_caminhosBin = (lista *)malloc(sizeof(lista) * (qtd_enderecos + 1));
    fptr = fopen("\\home\\heitor\\Documentos\\data\\doc_origem.txt", "rb");
    fread(ler_caminhosBin, sizeof(lista) * (qtd_enderecos + 1), 1, fptr);
    for (i = 0; i < qtd_enderecos; i++)
    {
        if (ler_caminhosBin[i].endereco[0] == '0')
            break;
        printf("\n%d --> %s\n\n", i + 1, ler_caminhosBin[i].endereco);
    }
    fclose(fptr);

    int comparativo[qtd_enderecos], x;
    n_pasta = -1;
    for (x = 0; x < qtd_enderecos; x++)
    {
        comparativo[x] = -1;
    }
    fptr = fopen("\\home\\heitor\\Documentos\\data\\docs_alvo.txt", "w");
    while (n_pasta != 0)
    {
        scanf("%d%*c", &n_pasta);
        if (n_pasta == 0)
        {
            break;
        }
        if (comparativo[n_pasta - 1] == 1)
        {
            printf("\nJÁ SELECIONADO ANTERIORMENTE, POR FAVOR ESCOLHA OUTRO ENDEREÇO OU ENCERRE O PROGRAMA\n\n");
            continue;
        }
        comparativo[n_pasta - 1] = 1;
        ftemp = fopen("", "w");
        fclose(ftemp);
        printf("%s SELECIONADO\n", ler_caminhosBin[n_pasta - 1].endereco);
        fprintf(fptr, "%s\n", ler_caminhosBin[n_pasta - 1].endereco);
    }
    fclose(fptr);
}