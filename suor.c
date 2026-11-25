// Nome: Yuri Antonio de Paula; RA: 259692; Nome: Saulo Barroso Castro; RA: 199121

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {

    int n;
    int m;

    int primeiro = -1;
    int anterior = -1;
    int atual = INT_MAX;
    int aux = -1;
    long long soma = 0;
    int indice = -1;

    scanf("%d", &n);
    scanf("%d", &m);

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &aux);
            int flag = 1;
            if (j != anterior && aux <= atual && (i == n - 1 && j != 0)) {
                atual = aux;
                indice = j;
                if (i = 0) {
                    primeiro = indice;
                }
                flag = 0;
            }
            if (flag) {
                printf("-1");
                return -1;
            }
        }
        soma += atual;
        anterior = indice;
    }

    printf(soma);

}