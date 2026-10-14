#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <windows.h>
#include <winbase.h>

#include "configs.h"
#include "copia/copia.h"
#include "docs/docs.h"




/**************************************
        Funções internas
***************************************/


/*
Função que verifica se um dado arquivo é um pasta. Retorna verdadeiro caso positivo e falso caso contrário.

Parâmetro:
    - DWORD dwFileAttributes: é um campo de uma instântica de estrutura DWORD. Isto é, ao encontrar um arquivo usando FindFile, o elemento retornado de estrutura WIN_FIND_DATA possuirá um campo com mesmo nome e tipo do parâmetro.
*/
bool e_pasta(DWORD dwFileAttributes)
{
    if(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        return true;
    else
        return false;
}

/*
Função que cria uma pasta no destino. Possuirá o mesmo nome de uma pasta src, mas será criada no caminho de destino definido (geralmente a pasta Backups ou subpastas de lá)
*/
void mk_dest_dir(const char *src, const char *dest)
{
    char dirName[CAMINHOS_TAM_MAX];
    strcpy(dirName, (strrchr(src, '\\') + 1));

    // É o caminho da pasta que precisa ser criada.
    char *dirPath = criar_dest_path(dirName, dest);

    printf("%s\n", dirPath);
    if(CreateDirectoryA(dirPath, NULL))
    {
        printf("Sucesso. Pasta criada em: %s\n", dirPath);

    } else {
        printf("Erro ao criar pasta em %s.\n", dirPath);
    }

    free(dirPath);
}


/*
Função que copia um único arquivo do seu caminho original, passado em src, para seu novo diretório de destino (dest).
*/
void copy_file(const char *src, const char *dest)
{
    char copy_dest[CAMINHOS_TAM_MAX];
    sprintf(copy_dest, "%s%s", dest, strrchr(src, '\\'));

    if(CopyFile(src, copy_dest, true))
    {
        printf("\nArquivo copiado com sucesso em %s...\n", src);
        printf("Copiado para: %s\n", copy_dest);
    }
    else
    {
        printf("\nFalha ao copiar arquivo em %s\n", src);
        printf("Erro: (%ld)\n", GetLastError());
    }
}



/**************************************
        Funções externas
***************************************/


/*
Procedimento que copia um diretório por seu caminho original ( passado em src ) para um destino final (passado em dest).

Parâmetros:
    - "src": Caminho para uma pasta com documentos que se deseja copiar.

    - "dest": É o endereço final onde ficarão as cópias. Na primeira chamada, receberá o caminho para a pasta padrão Backups ou pasta onde as cópias serão feitas. O procedimento montará os caminhos subsequentes para lidar com a recursividade. 
*/
void copy_dir(const char *src, const char *dest)
{
    // Preparando caminho para a busca
    char busca[CAMINHOS_TAM_MAX];
    strcpy(busca, src);
    strcat(busca, "\\*");

    // Iniciando handle e buscando informações de "src"

    WIN32_FIND_DATA docData;
    HANDLE hFind;
    DWORD dwError;

    hFind = FindFirstFile(busca, &docData);
    if(hFind == INVALID_HANDLE_VALUE)
    {
        printf("Não foi possível encontrar a pasta em %s.\n", busca);
        printf("ERRO: (%ld)\n", GetLastError());
        return;
    }

    // Se a busca for bem suscedida, cria um "espelho" da pasta atual no destino
    mk_dest_dir(src, dest);

    // Criando "próximo caminho de destino", trata-se de um caminho que apontará para a cópia da pasta atual criada no destino passado em "dest"
    char prox_dest[CAMINHOS_TAM_MAX];
    sprintf(prox_dest, "%s%s", dest, strrchr(src, '\\'));

    // Pula referências par e filho "." e ".."
    while(docData.cFileName[0] == '.' && FindNextFile(hFind, &docData) != 0);

    dwError = GetLastError();
    if(dwError == ERROR_NO_MORE_FILES)
        return;


    do
    {
        // Criando próxima src para a pasta ou arquivo atual
        char prox_src[CAMINHOS_TAM_MAX];
        sprintf(prox_src, "%s\\%s", src, docData.cFileName);


        if(e_pasta(docData.dwFileAttributes))
        {
            printf("\nÉ uma pasta: %s\n", docData.cFileName);
            
            // Chamando função para a próxima pasta encontrada
            copy_dir(prox_src, prox_dest);
        }
        else
        {
            // Se não for pasta, fazer a cópia do arquivo para todo arquivo na pasta atual
            printf("É um arquivo: %s\n", docData.cFileName);

            copy_file(prox_src, prox_dest);
        }

    } while (FindNextFile(hFind, &docData) != 0);
    
    // Verificando se houve algum erro ao copiar o diretório
    dwError = GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
    {
        printf("Não foi possível copiar o diretório.\n");
        printf("ERRO: (%ld)", dwError);
    }

    FindClose(hFind); // Liberando o ponteiro
}


bool copy_doc(const char *src, const char *dest)
{
    WIN32_FIND_DATA docData;
    HANDLE hFind;

    hFind = FindFirstFile(src, &docData);
    if(hFind == INVALID_HANDLE_VALUE)
    {
        printf("Não foi possível encontrar doc em %s.\n", src);
        printf("ERRO: (%ld)\n", GetLastError());
        return false;
    }

    if(e_pasta(docData.dwFileAttributes))
    {
        FindClose(hFind);
        copy_dir(src, dest);
    }
    else
    {
        FindClose(hFind);
        copy_file(src, dest);
    }

    return true;
}
