#include <stdio.h>

int n, k;
int matrix[27][27];
int count = 0;

void choose(int index, int chosen_count, int consecutive, int chosen[]) {
    if (chosen_count == k) {
        if (consecutive >= k/2) count++;
        return;
    }
    if (index == n) return;

    // Prune if not enough elements left
    if (chosen_count + (n - index) < k) return;

    int new_consec = consecutive;
    if (chosen_count > 0 && matrix[chosen[chosen_count-1]][index])
        new_consec++;

    chosen[chosen_count] = index;
    choose(index + 1, chosen_count + 1, new_consec, chosen);
    choose(index + 1, chosen_count, consecutive, chosen);
}


int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    int chosen[k];
    choose(0, 0, 0, chosen);

    printf("%d\n", count);
    return 0;
}