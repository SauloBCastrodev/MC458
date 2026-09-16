#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
    int id;
    int ordemX;
} Ponto;

typedef struct {
    int u;
    int v;
} Par;

typedef struct {
    long long dist;
    Par* pares;
    int qtd;
} Resultado;

int comparaX(const void* a, const void* b);
int comparaY(const void* a, const void* b);
int comparaPar(const void* a, const void* b);

long long distancia(Ponto p1, Ponto p2) {
    long long dx = (long long)p1.x - p2.x;
    long long dy = (long long)p1.y - p2.y;
    return dx * dx + dy * dy;
}

void adicionarPar(Resultado* res, int id1, int id2) {
    res->pares = realloc(res->pares, (res->qtd + 1) * sizeof(Par));
    res->pares[res->qtd].u = (id1 < id2) ? id1 : id2;
    res->pares[res->qtd].v = (id1 < id2) ? id2 : id1;
    res->qtd++;
}

Resultado acharMenoresDistancias(Ponto* pontos, int inicio, int fim) {
    int tamanho = fim - inicio + 1;
    Resultado res;
    res.dist = LLONG_MAX;
    res.pares = NULL;
    res.qtd = 0;

    // Ao invés de um monte de if, vai checando se a distância é menor, e vai substituindo ou adicionando com base nisso
    if (tamanho <= 3) {
        for (int i = inicio; i <= fim; i++) {
            for (int j = i + 1; j <= fim; j++) {
                long long d = distancia(pontos[i], pontos[j]);
                if (d < res.dist) {
                    res.dist = d;
                    free(res.pares);
                    res.pares = NULL;
                    res.qtd = 0;
                    adicionarPar(&res, pontos[i].id, pontos[j].id);
                }
                else if (d == res.dist) {
                    adicionarPar(&res, pontos[i].id, pontos[j].id);
                }
            }
        }
        return res;
    }

    int meio = inicio + (fim - inicio) / 2;
    int xMeio = pontos[meio].x;

    // Chamadas recursivas, dividindo em duas metades o problema
    Resultado esq = acharMenoresDistancias(pontos, inicio, meio);
    Resultado dir = acharMenoresDistancias(pontos, meio + 1, fim);

    // Checagens pra achar o lado com menor distância, ou checar se os dois lados tem a mesma menor distância
    if (esq.dist < dir.dist) {
        res.dist = esq.dist;
        res.pares = esq.pares;
        res.qtd = esq.qtd;
        free(dir.pares);
    }

    else if (esq.dist > dir.dist) {
        res.dist = dir.dist;
        res.pares = dir.pares;
        res.qtd = dir.qtd;
        free(esq.pares);
    }

    else {
        res.dist = esq.dist;
        res.pares = esq.pares;
        res.qtd = esq.qtd;
        for (int i = 0; i < dir.qtd; i++) {
            adicionarPar(&res, dir.pares[i].u, dir.pares[i].v);
        }
        free(dir.pares);
    }

    // Checa os pontos que estao proximos da divisão
    Ponto* faixa = malloc(tamanho * sizeof(Ponto));
    int qtdFaixa = 0;

    for (int i = inicio; i <= fim; i++) {
        long long dx = (long long)pontos[i].x - xMeio;
        if (dx * dx <= res.dist) {
            faixa[qtdFaixa] = pontos[i];
            qtdFaixa++;
        }
    }

    qsort(faixa, qtdFaixa, sizeof(Ponto), comparaY);

    for (int i = 0; i < qtdFaixa; i++) {
        for (int j = i + 1; j < qtdFaixa; j++) {
            long long dy = (long long)faixa[j].y - faixa[i].y;
            if (dy * dy > res.dist) {
                break;
            }

            if ((faixa[i].ordemX <= meio && faixa[j].ordemX <= meio) ||
                (faixa[i].ordemX > meio && faixa[j].ordemX > meio)) {
                continue;
            }

            long long d = distancia(faixa[i], faixa[j]);
            if (d < res.dist) {
                res.dist = d;
                free(res.pares);
                res.pares = NULL;
                res.qtd = 0;
                adicionarPar(&res, faixa[i].id, faixa[j].id);
            }
            else if (d == res.dist) {
                adicionarPar(&res, faixa[i].id, faixa[j].id);
            }
        }
    }

    free(faixa);

    return res;
}

// Função auxiliar que compara as coordenadas x para usar no qsort
int comparaX(const void* a, const void* b) {
    Ponto* p1 = (Ponto*)a;
    Ponto* p2 = (Ponto*)b;

    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}

int comparaY(const void* a, const void* b) {
    Ponto* p1 = (Ponto*)a;
    Ponto* p2 = (Ponto*)b;

    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

int comparaPar(const void* a, const void* b) {
    Par* p1 = (Par*)a;
    Par* p2 = (Par*)b;

    if (p1->u < p2->u) return -1;
    if (p1->u > p2->u) return 1;
    if (p1->v < p2->v) return -1;
    if (p1->v > p2->v) return 1;
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Ponto* pontos = (Ponto*)malloc(n * sizeof(Ponto));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pontos[i].x, &pontos[i].y);
        pontos[i].id = i;
    }

    // qsort é O(nlogn)
    qsort(pontos, n, sizeof(Ponto), comparaX);
    for (int i = 0; i < n; i++) {
        pontos[i].ordemX = i;
    }

    Resultado res = acharMenoresDistancias(pontos, 0, n - 1);

    qsort(res.pares, res.qtd, sizeof(Par), comparaPar);
    for (int i = 0; i < res.qtd; i++) {
        printf("(%d,%d)\n", res.pares[i].u, res.pares[i].v);
    }

    free(res.pares);
    free(pontos);
    return 0;
}