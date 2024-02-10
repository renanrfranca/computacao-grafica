# Atividade 4

Nesta ativadade, utilizamos raios para criar a imagem de uma esfera, um triângulo e um objeto .obj

## Como compilar

Primeiro geramos os build files com `cmake` a partir do diretório raíz desta atividade

`cmake -S . -B build`

Então podemos ir ao diretório `build` e compilar o projeto com `make`

`cd build && make`

Após uma execução bem sucedida do executável `Atividade04`, as seguintes imagens serão geradas no diretório, nos formantos ppm e png:

| Esfera                                       | Triângulo                                      | Objeto (Bule)                                |
|:--------------------------------------------:|:----------------------------------------------:|:--------------------------------------------:|
| <img src="./results/sphere.png" width="120"> | <img src="./results/triangle.png" width="120"> | <img src="./results/object.png" width="120"> |

Para rodar os testes, basta rodar o `ctest`, ainda dentro o diretório build

`ctest`