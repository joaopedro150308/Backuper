#ifndef UTEIS_H
#define UTEIS_H


/*
Função que limpa a tela do cmd independente do sistema operacional
*/
void limpar_cmd();


/*********************************
        Funções de i/o
*********************************/

/*
Função que imprime uma menssagem (passada em msg), lê e retorna um número inteiro digitado pelo usuário. Utiliza fgets e recursos para a segurânça
*/
int ler_inteiro(const char *msg);


/*
Função que imprime uma menssagem e, em seguida, lê e retorna uma string.

Paraâmetros:
    - retorno: é o ponteiro para um array de caracteres para onde a menssagem será retornada/copiada
*/
char *ler_string(const char *msg, char *retorno);






#endif