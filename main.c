#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long inteiro;

inteiro fat(int x) {
    if (x <= 1) return 1;
    return x * fat(x - 1);
}

inteiro arr(int total, int tam) {
    inteiro res = 1;
    int k = total;
    while (k > total - tam) {
        res *= k;
        k--;
    }
    return res;
}

inteiro comb(int total, int tam) {
    inteiro res = 1;
    int menor = (tam < total - tam) ? tam : total - tam;
    for (int k = 1; k <= menor; k++) {
        res *= total - menor + k;
        res /= k;
    }
    return res;
}

int digitos(inteiro v) {
    int d = 1;
    while (v >= 10) {
        v /= 10;
        d++;
    }
    return d;
}

void pascal(int altura) {
    int largura = digitos(comb(altura - 1, (altura - 1) / 2)) + 1;
    inteiro *linha = calloc(altura + 1, sizeof(inteiro));
    if (linha == NULL) return;

    linha[0] = 1;
    for (int i = 0; i < altura; i++) {
        printf("%*s", (altura - i - 1) * largura / 2, "");
        for (int j = 0; j <= i; j++)
            printf("%*llu", largura, linha[j]);
        printf("\n");
        for (int j = i + 1; j > 0; j--)
            linha[j] += linha[j - 1];
    }
    free(linha);
}

int proxima(int *v, int n) {
    int i = n - 2;
    while (i >= 0 && v[i] >= v[i + 1]) i--;
    if (i < 0) return 0;
    int j = n - 1;
    while (v[j] <= v[i]) j--;
    int t = v[i]; v[i] = v[j]; v[j] = t;
    for (int a = i + 1, b = n - 1; a < b; a++, b--) {
        t = v[a]; v[a] = v[b]; v[b] = t;
    }
    return 1;
}

void listar(int n) {
    int v[10];
    int num = 1;
    for (int i = 0; i < n; i++) v[i] = i + 1;
    do {
        printf("%d) ", num++);
        for (int i = 0; i < n; i++) printf("%d ", v[i]);
        printf("\n");
    } while (proxima(v, n));
}

int pedir(const char *texto, int ini, int fim) {
    int valor;
    for (;;) {
        printf("%s", texto);
        if (scanf("%d", &valor) == 1 && valor >= ini && valor <= fim)
            return valor;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Valor invalido.\n");
    }
}

int main(void) {
    for (;;) {
        printf("\n1 - Triangulo de Pascal\n");
        printf("2 - Arranjo\n");
        printf("3 - Permutacao Simples\n");
        printf("4 - Combinacao\n");
        printf("0 - Sair\n");
        int escolha = pedir("Escolha: ", 0, 4);

        if (escolha == 0) break;

        if (escolha == 1) {
            int h = pedir("Linhas (1-20): ", 1, 20);
            printf("\n");
            pascal(h);
        } else if (escolha == 2) {
            int n = pedir("n (0-20): ", 0, 20);
            int p = pedir("p: ", 0, n);
            printf("A(%d,%d) = %llu\n", n, p, arr(n, p));
        } else if (escolha == 3) {
            int n = pedir("n (0-20): ", 0, 20);
            printf("P(%d) = %llu\n", n, fat(n));
            if (n >= 1 && n <= 5) {
                char r;
                printf("Listar? (s/n): ");
                scanf(" %c", &r);
                if (r == 's' || r == 'S') listar(n);
            }
        } else {
            int n = pedir("n (0-60): ", 0, 60);
            int p = pedir("p: ", 0, n);
            printf("C(%d,%d) = %llu\n", n, p, comb(n, p));
        }
    }
    return 0;
}
