#ifndef BACKUPS_H
#define BACKUPS_H


/*
-> Função que cria o nome para uma basta de backup. Esse nome será também a data no momento atual.

:param retorno: Um ponteiro para onde o nome criado será copiado.
:return: 0 caso tudo ocorra bem. Caso contrário, retorna um número não nulo e nada é copiado para "retorno".
*/
int criar_nome_pasta(char *retorno);


/*
-> Cria uma sub pasta na pasta Bakcup tida como padrão. A pasta criada terá como nome a data no momento atual e servirá para conter os documentos copiados no backup

:param pasta_nome: Nome que a pasta criada terá. Será também a data do dia em que foi criada.
:return: A função retorna 0 se tudo ocorrer bem. Caso contrário, um número não nulo.
*/
int criar_pasta_para_backup(const char *pasta_nome);






#endif