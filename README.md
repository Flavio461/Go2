Projeto: Biblioteca de Menus para Terminal (CMD)

Especificações Técnicas Obrigatórias

Desenvolver uma biblioteca para criação de programas de linha de comando com menus de opções. Os menus são modelados como rotas com hierarquia (pai e filho), suporte a funções/ações e payloads, permitindo definir comportamentos e recuperar dados a partir de rotas superiores. Inclui um utilitário de navegação que mantém o histórico de forma otimizada por meio de uma linked list reversa, além de uma integração simples com um “banco de dados” baseado em arquivos locais para persistência.

Este projeto foi um exercício focado em estruturas de dados, ponteiros e desenho de APIs para CLI, com vários ajustes e pesquisas para torná-lo funcional, incluindo a solução para a limitação de callbacks não capturarem variáveis de escopo: adotou-se a passagem explícita de um parâmetro de contexto (semelhante ao “self” em Python) para que os handlers acessem o estado necessário.

Tecnologias utilizadas:

C++ para a biblioteca e utilitários de linha de comando;
Compilação com GCC e CMake;
Estruturas encadeadas (linked list reversa) para histórico de navegação;
Persistência em arquivos locais (leitura/escrita simples).

O que aprendi:

Estruturas de dados e ponteiros: implementação de linked list reversa para histórico, manipulação segura de nós e referências;
Roteamento e hierarquia de menus: definição de rotas pai/filho, propagação de payloads e recuperação de dados de rotas superiores;
Callbacks e contexto (“self”): passagem de um ponteiro de contexto para simular captura de escopo em funções e padronizar handlers;
Persistência em arquivos: leitura/escrita para armazenamento local, garantindo consistência simples e reprodutibilidade;
Tratamento de erros e UX em CLI: validação de entrada, mensagens claras e navegação eficiente no terminal.
