#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000

int min(int a, int b) {
    return a < b ? a : b;
}

int calculateMinimumCost(int N, int M, int K, char originalRoute[], char newRoute[]) {
    int dp[N + 1][M + 1];

    for (int i = 0; i <= N; i++)
        dp[i][0] = i * 3;

    for (int j = 0; j <= M; j++)
        dp[0][j] = j * 3;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (originalRoute[i - 1] == newRoute[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                if (originalRoute[i - 1] == '#' && newRoute[j - 1] != '#') {
                    dp[i][j] = min(dp[i - 1][j] + 2, dp[i][j - 1] + 1);
                } else if (originalRoute[i - 1] != '#' && newRoute[j - 1] == '#') {
                    dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 2);
                } else {
                    dp[i][j] = min(dp[i - 1][j] + 3, dp[i][j - 1] + 3);
                }
            }
        }
    }

    if (dp[N][M] <= K) {
        return K - dp[N][M];
    } else {
        return -1;
    }
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    char originalRoute[N + 1], newRoute[M + 1];
    scanf("%s %s", originalRoute, newRoute);

    int result = calculateMinimumCost(N, M, K, originalRoute, newRoute);

    if (result != -1) {
        printf("Lucro: %d. A caminho!\n", result);
    } else {
        printf("Carona inviavel, favor solicitar outra nave.\n");
    }

    return 0;
}
