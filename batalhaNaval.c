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

    // Vetores que representam os quatro navios de tamanho 3.
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioDiagonal1[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};  // Diagonal para baixo-direita
    int navioDiagonal2[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};  // Diagonal para baixo-esquerda

    // Coordenadas iniciais definidas diretamente no código.
    // Os valores estão em formato [linha, coluna], onde 0 é a primeira linha/coluna.
    int linhaInicioHorizontal = 0;
    int colunaInicioHorizontal = 1;
    
    int linhaInicioVertical = 3;
    int colunaInicioVertical = 5;
    
    // Navio diagonal 1: posicionado na diagonal para baixo-direita (tabuleiro[i][i])
    // Começa na posição (1, 1) e vai até (3, 3)
    int linhaInicioDiagonal1 = 1;
    int colunaInicioDiagonal1 = 1;
    
    // Navio diagonal 2: posicionado na diagonal para baixo-esquerda (tabuleiro[i][9-i])
    // Começa na posição (6, 9) e vai até (8, 7)
    int linhaInicioDiagonal2 = 6;
    int colunaInicioDiagonal2 = 9;

    // Validação dos limites do tabuleiro para cada navio.
    int erro = 0;

    // Validação do navio horizontal
    if (linhaInicioHorizontal < 0 || linhaInicioHorizontal >= TAMANHO_TABULEIRO ||
        colunaInicioHorizontal < 0 || colunaInicioHorizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio horizontal estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

    // Validação do navio vertical
    if (linhaInicioVertical < 0 || linhaInicioVertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaInicioVertical < 0 || colunaInicioVertical >= TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio vertical estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

    // Validação do navio diagonal 1 (diagonal para baixo-direita)
    // Verifica se a linha inicial + tamanho-1 está dentro dos limites
    // e se a coluna inicial + tamanho-1 está dentro dos limites
    if (linhaInicioDiagonal1 < 0 || linhaInicioDiagonal1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaInicioDiagonal1 < 0 || colunaInicioDiagonal1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio diagonal 1 estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

    // Validação do navio diagonal 2 (diagonal para baixo-esquerda)
    // Verifica se a linha inicial + tamanho-1 está dentro dos limites
    // e se a coluna inicial - tamanho+1 está dentro dos limites
    if (linhaInicioDiagonal2 < 0 || linhaInicioDiagonal2 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaInicioDiagonal2 - TAMANHO_NAVIO + 1 < 0 || colunaInicioDiagonal2 >= TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio diagonal 2 estão fora dos limites do tabuleiro.\n");
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

    // Verifica sobreposição do navio diagonal 1 com os navios já posicionados.
    // O navio diagonal 1 vai de (i, i) até (i+2, i+2)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal1 + i;
        int coluna = colunaInicioDiagonal1 + i;

        if (tabuleiro[linha][coluna] != AGUA) {
            printf("Erro: sobreposição detectada com navio diagonal 1 nas coordenadas (%d, %d).\n", linha, coluna);
            return 1;
        }
    }

    // Posiciona o navio diagonal 1 no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal1 + i;
        int coluna = colunaInicioDiagonal1 + i;
        tabuleiro[linha][coluna] = navioDiagonal1[i];
    }

    // Verifica sobreposição do navio diagonal 2 com os navios já posicionados.
    // O navio diagonal 2 vai de (i, 9-i) até (i+2, 7-i)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal2 + i;
        int coluna = colunaInicioDiagonal2 - i;

        if (tabuleiro[linha][coluna] != AGUA) {
            printf("Erro: sobreposição detectada com navio diagonal 2 nas coordenadas (%d, %d).\n", linha, coluna);
            return 1;
        }
    }

    // Posiciona o navio diagonal 2 no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal2 + i;
        int coluna = colunaInicioDiagonal2 - i;
        tabuleiro[linha][coluna] = navioDiagonal2[i];
    }

    // Exibe o tabuleiro completo no console.
    printf("\n=== Tabuleiro de Batalha Naval 10x10 ===\n");
    printf("Legenda: 0 = Água | 3 = Navio\n\n");
    
    // Exibe os números das colunas (0-9)
    printf("   ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++) {
        printf("%d ", col);
    }
    printf("\n");

    // Exibe o tabuleiro com números de linhas (0-9)
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        printf("%d: ", linha);
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\n=== Posicionamento dos Navios ===\n");
    printf("Navio Horizontal: Linha %d, Colunas %d-%d\n", linhaInicioHorizontal, colunaInicioHorizontal, colunaInicioHorizontal + TAMANHO_NAVIO - 1);
    printf("Navio Vertical: Coluna %d, Linhas %d-%d\n", colunaInicioVertical, linhaInicioVertical, linhaInicioVertical + TAMANHO_NAVIO - 1);
    printf("Navio Diagonal 1 (baixo-direita): Início (%d, %d), Fim (%d, %d)\n", linhaInicioDiagonal1, colunaInicioDiagonal1, linhaInicioDiagonal1 + TAMANHO_NAVIO - 1, colunaInicioDiagonal1 + TAMANHO_NAVIO - 1);
    printf("Navio Diagonal 2 (baixo-esquerda): Início (%d, %d), Fim (%d, %d)\n", linhaInicioDiagonal2, colunaInicioDiagonal2, linhaInicioDiagonal2 + TAMANHO_NAVIO - 1, colunaInicioDiagonal2 - TAMANHO_NAVIO + 1);

    return 0;
}
