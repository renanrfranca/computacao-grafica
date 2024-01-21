# Atividade 3

Nesta ativadade, lemos um arquivo obj, armazenando em listas vértices, vetores normais, informações de textura e faces contidas nele.

## Como compilar

Primeiro geramos os build files com `cmake` a partir do diretório raíz desta atividade

`cmake -S . -B build`

Então podemos ir ao diretório `build` e compilar o projeto com `make`

`cd build && make`

Exemplo de execução, utilizando o cube.obj incluído no projeto:

`./Atividade03 "../resources/cube.obj"`

Para rodar os testes, basta rodar o `ctest`, ainda dentro o diretório build

`ctest`