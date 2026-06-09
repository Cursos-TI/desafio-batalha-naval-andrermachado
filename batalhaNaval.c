#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este programa posiciona dois navios em um tabuleiro 10x10 utilizando matrizes e vetores.
// A matriz representa o tabuleiro e os vetores representam navios com tamanho fixo igual a 3.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Tabuleiro 10x10 inicializado com água (0).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Vetores que representam os dois navios de tamanho 3.
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // Coordenadas iniciais definidas diretamente no código.
    // Os valores estão em formato [linha, coluna], onde 0 é a primeira linha/coluna.
    int linhaInicioHorizontal = 2;
    int colunaInicioHorizontal = 4;
    int linhaInicioVertical = 5;
    int colunaInicioVertical = 7;

    // Validação dos limites do tabuleiro para cada navio.
    int erro = 0;

    if (linhaInicioHorizontal < 0 || linhaInicioHorizontal >= TAMANHO_TABULEIRO ||
        colunaInicioHorizontal < 0 || colunaInicioHorizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio horizontal estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

    if (linhaInicioVertical < 0 || linhaInicioVertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaInicioVertical < 0 || colunaInicioVertical >= TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio vertical estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

    if (erro) {
        return 1;
    }

    // Posiciona o navio horizontal no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicioHorizontal][colunaInicioHorizontal + i] = navioHorizontal[i];
    }

    // Verifica se o navio vertical irá se sobrepor ao navio horizontal.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioVertical + i;
        int coluna = colunaInicioVertical;

        if (tabuleiro[linha][coluna] != AGUA) {
            printf("Erro: sobreposição detectada entre navios nas coordenadas (%d, %d).\n", linha, coluna);
            return 1;
        }
    }

    // Posiciona o navio vertical no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicioVertical + i][colunaInicioVertical] = navioVertical[i];
    }

    // Exibe o tabuleiro completo no console.
    printf("Tabuleiro de Batalha Naval 10x10:\n");
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}
