#include <stdio.h>

int main() {
    int state[5][5];
    int rateLanes = 16, capacityLanes = 9;

    int laneIndex = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (laneIndex < rateLanes) state[x][y] = 1;
            else state[x][y] = 0;
            laneIndex++;
        }
    }

    printf("SHA-3 State Matrix (5x5 Lanes, Lane Width = 64 bits):\n");
    printf("Total Bits: 1600 | Block Size (Rate): 1024 bits (16 lanes) | Capacity: 576 bits (9 lanes)\n\n");

    printf("Initial State Matrix (1 = non-zero bit present, 0 = all zero lane):\n");
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) printf("%2d ", state[x][y]);
        printf("\n");
    }

    int zeroCountBefore = 0;
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            if (state[x][y] == 0) zeroCountBefore++;

    printf("\nInitial zero capacity lanes: %d\n", zeroCountBefore);

    int C[5] = {0};
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            C[x] |= state[x][y];

    int D[5] = {0};
    for (int x = 0; x < 5; x++)
        D[x] = C[(x + 4) % 5] | C[(x + 1) % 5];

    int round1State[5][5];
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            round1State[x][y] = state[x][y] | D[x];

    printf("\nState Matrix after Round 1 (Theta step):\n");
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) printf("%2d ", round1State[x][y]);
        printf("\n");
    }

    int zeroCountAfter = 0;
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            if (round1State[x][y] == 0) zeroCountAfter++;

    printf("\nRemaining zero lanes after Round 1: %d\n\n", zeroCountAfter);
    printf("Conclusion:\n");
    printf("It takes exactly 1 ROUND (specifically, the Theta step of Round 1)\n");
    printf("for all lanes in the capacity portion to have at least one nonzero bit.\n");

    return 0;
}
