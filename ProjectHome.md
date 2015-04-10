Trabalho 1 para SSC0642 - Sistemas Distribuídos.
USP - São Carlos

Especificação: O objetivo deste trabalho é realizar a ordenação de um vetor de 1000 posições utilizando sockets em C.

Para cumprir o objetivo serão necessários 8 clientes, onde cada cliente deverá gerar um vetor aleatório de 125 posições (1 nível).

No segundo nível deverá existir 4 servidores que receberão os vetores gerados no primeiro nível. Cada servidor deverá receber apenas 2 clientes e ordenar os respectivos vetores.

No terceiro nível deverá existir 2 servidores que receberão os vetores gerados no segundo nível.  Cada servidor deverá receber apenas 2 clientes e ordenar os respectivos vetores.

O último nível (Sevidor Principal) receberá os dois vetores e fará a ordenação total do vetor, gerando assim o vetor de 1000 posições. O vetor gerado deverá ser impresso em todos os clientes do 1 nível.