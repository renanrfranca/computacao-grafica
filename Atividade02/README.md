# Atividade 2

Nesta ativadade, geramos classes de vetores e matrizes, com diversas funções auxiliares. Também adicionamos testes usando a biblioteca GoogleTest.

## Como compilar

Primeiro geramos os build files com `cmake` a partir do diretório raíz desta atividade

`cmake -S . -B build`

Então podemos ir ao diretório `build` e compilar o projeto com `make`

`cd build && make`

Para rodar os testes, basta rodar o `ctest`, ainda dentro o diretório build

`ctest`