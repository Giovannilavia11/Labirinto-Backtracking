//NOMES----------------- RA -----
//Giovanni Alves Lavia - 10409448
//Samuel Lopes Pereira - 10403767

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//definiçao do tamanho maximo do labrinto
#define MAX_LINHAS 100
#define MAX_COLUNAS 100

//declaraçao da matriz e variaveis principais
char labirinto[MAX_LINHAS][MAX_COLUNAS];
int linhas, colunas;
bool encontrado = false;

// Função booleana para verificar se uma posição é válida no labirinto
bool posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas && (labirinto[linha][coluna] == '.' || labirinto[linha][coluna] == 'S'));
}

// Função para encontrar o caminho no labirinto
void encontrarCaminho(int linha, int coluna) {
    // Se a posição atual for a saída, definir encontrado como true
    if (labirinto[linha][coluna] == 'S') {
        encontrado = true;
        return;
    }

    // Marca a posição atual
    labirinto[linha][coluna] = 'o';

    // Movendo para cima
    if (!encontrado && posicaoValida(linha - 1, coluna)) {
        encontrarCaminho(linha - 1, coluna);
    }
    // Movendo para baixo
    if (!encontrado && posicaoValida(linha + 1, coluna)) {
        encontrarCaminho(linha + 1, coluna);
    }
    // Movendo para a esquerda
    if (!encontrado && posicaoValida(linha, coluna - 1)) {
        encontrarCaminho(linha, coluna - 1);
    }
    // Movendo para a direita
    if (!encontrado && posicaoValida(linha, coluna + 1)) {
        encontrarCaminho(linha, coluna + 1);
    }

    // Se o caminho não foi encontrado a partir desta posição, volta para a posição anterior e marca como não visitado
    if (!encontrado) {
        labirinto[linha][coluna] = '.';
    }
}

// Função para a impressão do labirinto
void imprimirLabirinto() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'o') {
                printf("\033[0;32m%c\033[0m", labirinto[i][j]); 
            } else {
                printf("%c", labirinto[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
   // Leitura do arquivo de entrada
    FILE *entrada = fopen("labirinto.txt", "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada!");
        return EXIT_FAILURE;
    }

    // Ler o tamanho do labirinto
    fscanf(entrada, "%d %d", &linhas, &colunas);

    // Ler o labirinto
    for (int i = 0; i < linhas; i++) {
        fscanf(entrada, "%s", labirinto[i]);
    }

    fclose(entrada);

    // Encontra o ponto de entrada do labirinto
    int entrada_linha, entrada_coluna;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'E' && i == 0) {
                entrada_linha = i + 1;
                entrada_coluna = j;
                break;
            }else if (labirinto[i][j] == 'E'){
                entrada_linha = i;
                entrada_coluna = j + 1;
                break;
            }
        }
    }

    // Encontrar o caminho
    encontrarCaminho(entrada_linha, entrada_coluna);

    printf("Caminho marcado no labirinto:\n\n");

    // Imprimir o labirinto com 'o'
    imprimirLabirinto();

    // Escrever o labirinto marcado no arquivo de saída
    FILE *saida = fopen("labirinto_saida.txt", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < linhas; i++) {
        fprintf(saida, "%s\n", labirinto[i]);
    }

    fclose(saida);

    printf("\nO caminho foi marcado no arquivo labirinto_saida.txt\n");

    return EXIT_SUCCESS;
}