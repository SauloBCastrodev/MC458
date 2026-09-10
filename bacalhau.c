#include <stdio.h>   
#include <stdlib.h>
#include <math.h>    
#include <float.h>

typedef struct {
    double x;
    double y;
    int id;
} Ponto;

typedef struct {
    int u;
    int v;
} Par;

typedef struct {
    double dist;
    Par* pares;
    int qtd;
} Resultado;

double distancia(Ponto p1, Ponto p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void adicionarPar(Resultado* res, int id1, int id2) {
    res->pares = realloc(res->pares, (res->qtd+1)*sizeof(Par));
    res->pares[res->qtd].u = (id1 < id2) ? id1 : id2;
    res->pares[res->qtd].v = (id1 < id2) ? id2 : id1;
    res->qtd++;
 }

Resultado acharMenoresDistancias(Ponto* pontos, int inicio, int fim) {
    int tamanho = fim - inicio + 1;
    Resultado res;
    res.dist = DBL_MAX;
    res.pares = NULL;
    res.qtd = 0;

    // Ao invés de um monte de if, vai checando se a distância é menor, e vai substituindo ou adicionando com base nisso
    if (tamanho <= 3) {
        for (int i = inicio; i <= fim; i++) {
            for (int j = i + 1; j <= fim; j++) {
                double d = distancia(pontos[i], pontos[j]);
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

    int meio = inicio + (fim - inicio)/2;
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
        for (int i = 0; i < dir.qtd; i++) {
            adicionarPar(&res.pares, dir.pares[i].u, dir.pares[i].v);
        }
        free(dir.pares);
    }

    // Checa todos os pontos 
    Ponto* faixa = malloc(tamanho*sizeof(Ponto));
    for (int i = inicio; i <= fim; i++) {
        if (fabs(pontos[i].x - pontos[i].x) < res.dist) {
            faixa[i] = pontos[i];
        }
    }

    qsort(faixa, tamanho, sizeof(Ponto), comparaY);

    for (int i = 0; i <= tamanho; i++) {
        for (int j = i + 1; j <= tamanho; j++) {
            if (faixa[j].y - faixa[i].y >= res.dist) {
                break;
            }
            double d = distancia(faixa[i], faixa[j]);
            if (d < res.dist) {
                res.dist = d;
                free(res.pares);
                adicionarPar(&res.pares, faixa[i].id, faixa[j].id);
            }
            if (d == res.dist) {
                adicionarPar(&res.pares, faixa[i].id, faixa[j].id);
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

int main() {

    int n;
    if (scanf("%d", &n) != 1) return 0;
    Ponto* pontos = (Ponto*)malloc(n*sizeof(Ponto));

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
        pontos[i].id = i;
    }

    // qsort é O(nlogn)
    qsort(pontos, n, sizeof(Ponto), comparaX);

    Resultado res = acharMenoresDistancias(pontos, 0, n - 1);

    free(pontos);
    return 0;

}