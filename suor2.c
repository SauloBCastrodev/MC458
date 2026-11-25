#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000000000LL

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
    long long melhor = INF;

    for (int f = 0; f < m; f++) {
        for (int j = 0; j < m; j++) {
            if (j == f) {
                dp[0][j] = c[0][j];
            }
            else { 
                dp[0][j] = INF;
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                long long min = INF;
                for(int z = 0; z < m; z++) {
                    if (dp[i-1][z] < min && z != j) {
                        min = dp[i-1][z];
                    }
                }
                dp[i][j] = c[i][j] + min;
            }
        }

        for (int j = 0; j < m; j++) {
            if (j != f && dp[n-1][j] < melhor) melhor = dp[n-1][j];
        }
    }

    if (melhor >= INF) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", melhor);
    }

}