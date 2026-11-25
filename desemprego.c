#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Chute guloso: Tenho A e B. Considere + como sendo concatenação e não soma. Se A + B > B + A, A vem antes de B, e o oposto também vale.

int comparacarta(void* a, void* b) {
    char* str_a = (char*)a;
    char* str_b = (char*)b;

    char ab[24];
    char ba[24];

    strcpy(ab, str_a);
    strcat(ab, str_b);

    strcpy(ba, str_b);
    strcat(ba, str_a);

    return(strcmp(ba, ab));

}

int main() {
    int n;

    scanf("%d", &n);

    char arranjo[n][12];

    for (int i = 0; i < n; i++) {
        scanf("%s", arranjo[i]);
    }

    qsort(arranjo, n, sizeof(arranjo[0]), comparacarta);

    for (int i = 0; i < n; i++) {
        printf("%s", arranjo[i]);
    }

    printf("\n");

}