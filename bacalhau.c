#include <stdio.h>   
#include <stdlib.h>
#include <math.h>    
#include <float.h>

typedef struct {
    float x;
    float y;
    int id;
} Ponto;

int main() {

    int n;
    if (scanf("%d", &n) != 1) return 0;
    Ponto* pontos = (Ponto*)malloc(n*sizeof(Ponto));

    for (int i = 0; i < n; i++) {
        scanf("%f %f", &pontos[i].x, &pontos[i].y);
        pontos[i].id = i;
    }

    free(pontos);
    return 0;
}