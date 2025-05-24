#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para imprimir o tabuleiro com representação visual
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");        // Água
            else if (tabuleiro[i][j] == 3) printf("# ");   // Navio
            else if (tabuleiro[i][j] == 5) printf("* ");   // Área de habilidade
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio (horizontal, vertical ou diagonal)
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int x, int y, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || ny < 0 || nx >= TAM_TABULEIRO || ny >= TAM_TABULEIRO || tabuleiro[nx][ny] != 0)
            return 0; // Fora do tabuleiro ou sobreposto
    }
    for (int i = 0; i < 3; i++) {
        tabuleiro[x + i * dx][y + i * dy] = 3;
    }
    return 1;
}

// Função para criar matriz de habilidade em forma de cone
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i) ? 1 : 0;
        }
    }
}

// Função para criar matriz de habilidade em forma de cruz
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Função para criar matriz de habilidade em forma de octaedro
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - TAM_HABILIDADE / 2) + abs(j - TAM_HABILIDADE / 2) <= TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Função para aplicar a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int x, int y) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int ti = x + i - TAM_HABILIDADE / 2;
            int tj = y + j - TAM_HABILIDADE / 2;
            if (ti >= 0 && tj >= 0 && ti < TAM_TABULEIRO && tj < TAM_TABULEIRO && habilidade[i][j] == 1) {
                if (tabuleiro[ti][tj] == 0) {
                    tabuleiro[ti][tj] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionando navios fixamente
    posicionarNavio(tabuleiro, 0, 0, 0, 1);  // Horizontal
    posicionarNavio(tabuleiro, 2, 2, 1, 0);  // Vertical
    posicionarNavio(tabuleiro, 4, 4, 1, 1);  // Diagonal principal
    posicionarNavio(tabuleiro, 2, 7, 1, -1); // Diagonal secundária

    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 1, 5);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 8, 2);

    imprimirTabuleiro(tabuleiro);

    return 0;
}