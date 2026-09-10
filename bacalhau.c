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

    if (tamanho == 2) {
        res.dist = distancia(pontos[inicio], pontos[fim]);
        adicionarPar(&res, pontos[inicio].id, pontos[fim].id);
        return res;
    }

    // Refazer para caso base 3
    if (tamanho == 3) {
        double d1 = distancia(pontos[inicio], pontos[inicio + 1]);
        double d2 = distancia(pontos[inicio], pontos[fim]);
        double d3 = distancia(pontos[inicio + 1], pontos[fim]);

        

    }

    int meio = inicio + (fim - inicio)/2;
    Resultado esq = acharMenoresDistancias(pontos, inicio, meio);
    Resultado dir = acharMenoresDistancias(pontos, meio + 1, fim);
    
    if (esq.dist < dir.dist) {
        res.dist = esq.dist;
        res.pares = esq.pares;
        res.qtd = esq.qtd;
    }

    else if (esq.dist > dir.dist) {
        res.dist = dir.dist;
        res.pares = dir.pares;
        res.qtd = dir.qtd;
    }

    else {
        res.dist = esq.dist;
        res.pares = esq.pares;
        for (int i = 0; i < (fim - meio - 1); i++) {
            adicionar(&res.pares, dir.pares[i].u, dir.pares[i].v);
        }
    }

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

    free(pontos);
    return 0;
}