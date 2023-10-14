#include <stdio.h>
#include <stdbool.h>

int maximize_value(int N, int D, int items[][2], int M, int incompatibilities[][2], int item_index, int current_value, int current_weight, int chosen[])
{
    if (item_index == N)
    {
        return current_value;
    }

    bool is_compatible = true;
    for (int i = 0; i < M; i++)
    {
        if (incompatibilities[i][0] == item_index + 1 && chosen[incompatibilities[i][1] - 1] == 1)
        {
            is_compatible = false;
            break;
        }
        if (incompatibilities[i][1] == item_index + 1 && chosen[incompatibilities[i][0] - 1] == 1)
        {
            is_compatible = false;
            break;
        }
    }

    int max_value = maximize_value(N, D, items, M, incompatibilities, item_index + 1, current_value, current_weight, chosen);

    if (is_compatible && current_weight + items[item_index][1] <= D)
    {
        chosen[item_index] = 1;
        int value_with_item = maximize_value(N, D, items, M, incompatibilities, item_index + 1, current_value + items[item_index][0], current_weight + items[item_index][1], chosen);
        chosen[item_index] = 0;
        max_value = (value_with_item > max_value) ? value_with_item : max_value;
    }

    return max_value;
}

int main()
{
    int N, D, M;
    scanf("%d %d", &N, &D);
    int items[N][2];
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &items[i][0], &items[i][1]);
    }
    scanf("%d", &M);
    int incompatibilities[M][2];
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &incompatibilities[i][0], &incompatibilities[i][1]);
    }

    int chosen[N];
    for (int i = 0; i < N; i++)
    {
        chosen[i] = 0;
    }

    int result = maximize_value(N, D, items, M, incompatibilities, 0, 0, 0, chosen);
    printf("%d\n", result);

    return 0;
}
