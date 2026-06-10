#include <stdio.h>
#include <stdlib.h>

// Desafio Batalha Naval - MateCheck
// Este programa posiciona navios em um tabuleiro 10x10 e exibe áreas de efeito
// de habilidades especiais no mesmo tabuleiro.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_ATAQUE 5
#define TAMANHO_HABILIDADE 5

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

    // Navio diagonal 1: posicionado na diagonal para baixo-direita
    int linhaInicioDiagonal1 = 1;
    int colunaInicioDiagonal1 = 1;

    // Navio diagonal 2: posicionado na diagonal para baixo-esquerda
    int linhaInicioDiagonal2 = 6;
    int colunaInicioDiagonal2 = 9;

    // Pontos de origem para as habilidades especiais no tabuleiro.
    // O ponto de origem define o centro da área de efeito.
    int origemConeLinha = 2;
    int origemConeColuna = 7;

    int origemCruzLinha = 6;
    int origemCruzColuna = 2;

    int origemOctaedroLinha = 7;
    int origemOctaedroColuna = 5;

    // Matrizes de habilidade 5x5 que indicam a área de efeito com 1 e áreas não afetadas com 0.
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    int meioHabilidade = TAMANHO_HABILIDADE / 2;

    // Constroi dinamicamente as matrizes de habilidade usando loops aninhados e condicionais.
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            cone[i][j] = 0;
            cruz[i][j] = 0;
            octaedro[i][j] = 0;

            // Cone: ponto de origem no topo e expandindo para baixo.
            if ((i == 0 && j == meioHabilidade) ||
                (i == 1 && j >= meioHabilidade - 1 && j <= meioHabilidade + 1) ||
                (i == 2)) {
                cone[i][j] = 1;
            }

            // Cruz: ponto de origem no centro, linhas vertical e horizontal.
            if (i == meioHabilidade || j == meioHabilidade) {
                cruz[i][j] = 1;
            }

            // Octaedro (vista frontal): formato de losango centrado.
            if (abs(i - meioHabilidade) + abs(j - meioHabilidade) <= meioHabilidade) {
                octaedro[i][j] = 1;
            }
        }
    }

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

    if (linhaInicioDiagonal1 < 0 || linhaInicioDiagonal1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        colunaInicioDiagonal1 < 0 || colunaInicioDiagonal1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: coordenadas do navio diagonal 1 estão fora dos limites do tabuleiro.\n");
        erro = 1;
    }

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

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicioVertical + i][colunaInicioVertical] = navioVertical[i];
    }

    // Verifica e posiciona o navio diagonal 1 no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal1 + i;
        int coluna = colunaInicioDiagonal1 + i;
        if (tabuleiro[linha][coluna] != AGUA) {
            printf("Erro: sobreposição detectada com navio diagonal 1 nas coordenadas (%d, %d).\n", linha, coluna);
            return 1;
        }
        tabuleiro[linha][coluna] = navioDiagonal1[i];
    }

    // Verifica e posiciona o navio diagonal 2 no tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicioDiagonal2 + i;
        int coluna = colunaInicioDiagonal2 - i;
        if (tabuleiro[linha][coluna] != AGUA) {
            printf("Erro: sobreposição detectada com navio diagonal 2 nas coordenadas (%d, %d).\n", linha, coluna);
            return 1;
        }
        tabuleiro[linha][coluna] = navioDiagonal2[i];
    }

    // Sobrepõe as áreas de efeito de cada habilidade no tabuleiro.
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (cone[i][j] == 1) {
                int linha = origemConeLinha + i - meioHabilidade;
                int coluna = origemConeColuna + j - meioHabilidade;
                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = AREA_ATAQUE;
                    }
                }
            }

            if (cruz[i][j] == 1) {
                int linha = origemCruzLinha + i - meioHabilidade;
                int coluna = origemCruzColuna + j - meioHabilidade;
                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = AREA_ATAQUE;
                    }
                }
            }

            if (octaedro[i][j] == 1) {
                int linha = origemOctaedroLinha + i - meioHabilidade;
                int coluna = origemOctaedroColuna + j - meioHabilidade;
                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = AREA_ATAQUE;
                    }
                }
            }
        }
    }

    // Exibe o tabuleiro completo no console.
    printf("\n=== Tabuleiro de Batalha Naval 10x10 ===\n");
    printf("Legenda: 0 = Água | 3 = Navio | 5 = Área afetada pela habilidade\n\n");

    printf("   ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++) {
        printf("%d ", col);
    }
    printf("\n");

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

    printf("\n=== Habilidades de Área de Efeito ===\n");
    printf("Cone: origem (%d, %d)\n", origemConeLinha, origemConeColuna);
    printf("Cruz: origem (%d, %d)\n", origemCruzLinha, origemCruzColuna);
    printf("Octaedro: origem (%d, %d)\n", origemOctaedroLinha, origemOctaedroColuna);

    return 0;
}
