// Nome: Yuri Antonio de Paula; RA: 259692; Nome: Saulo Barroso Castro; RA: 199121  

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000000000000LL

int main() {

    long long c[1000][100];
    int n;
    int m;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%lld", &c[i][j]);
        }
    }

    long long dp[1000][100];
    long long melhor = MAX;

    for (int f = 0; f < m; f++) {
        for (int j = 0; j < m; j++) {
            if (j == f) {
                dp[0][j] = c[0][j];
            }
            else { 
                dp[0][j] = MAX;
            }
        }

        for (int i = 1; i < n; i++) {
            long long min1 = MAX, min2 = MAX;
            int cor1 = -1;
            for(int z = 0; z < m; z++) {
                    if(dp[i-1][z] < min1) {
                        min2 = min1;
                        min1 = dp[i-1][z];
                        cor1 = z;
                    } else if (dp[i-1][z] < min2) {
                        min2 = dp[i-1][z];
                    }
            }
            for (int j = 0; j < m; j++) {
                long long melhorAnt = (j != cor1) ? min1 : min2;
                dp[i][j] = c[i][j] + melhorAnt;
            }
        }

        for (int j = 0; j < m; j++) {
            if (j != f && dp[n-1][j] < melhor) melhor = dp[n-1][j];
        }
    }

    if (melhor >= MAX) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", melhor);
    }

}