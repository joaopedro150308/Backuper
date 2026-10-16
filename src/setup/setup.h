/*
Esse módulo deve lidar com os seguintes problemas:

    1 - Leitura dos caminhos para os documentos que serão copiados no processo de backup
    2 - Registrar esses caminhos em arquivo(os) persistentes

    - Para realizar (2), é necessário que o programa seja capaz de gerar um "setup" próprio, independente do sistema do usuário. Isto é, após distribuir o executável, ao rodá-lo, o mesmo deve ser capaz de encontrar e, se necessário, gerar as pastas e arquivos necessários para a sua correta execução. É importante salientar que, dentre os diretórios e arquivos necessários, existirão aqueles que serão uteis apenas ao programa e aqueles que o usuário pode manipular.
    
    Como exemplo de diretórios próprios apenas do sistema, pode-se citar a lista com os caminhos, sua contagem, dados análiticos e internos que, em resumo, nada dizem ao usuário. Por outro lado, é interessante que o usuário possa, por exemplo, manipular o local onde a pasta que guardará os backups ficará em seu sistema, pois, afinal, ter acesso a esses lhe é bastante útil.

    Desse modo, para rodar o programa com segurânça, deve-se passar antes pela etapa de verificação do "setup", garantindo que todos os arquivos existam e/ou sejam criados corretamente.
        


*/

#ifndef SETUP_H
#define SETUP_H




#endif