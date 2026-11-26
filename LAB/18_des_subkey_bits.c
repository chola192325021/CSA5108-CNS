#include <stdio.h>

int main() {
    int PC2[48] = {
        14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };

    int c_valid = 1, d_valid = 1;

    printf("PC-2 First 24 bits (from C half, bits 1-28):\n");
    for (int i = 0; i < 24; i++) {
        printf("%2d ", PC2[i]);
        if (PC2[i] < 1 || PC2[i] > 28) c_valid = 0;
        if ((i + 1) % 12 == 0) printf("\n");
    }

    printf("\nPC-2 Second 24 bits (from D half, bits 29-56):\n");
    for (int i = 24; i < 48; i++) {
        printf("%2d ", PC2[i]);
        if (PC2[i] < 29 || PC2[i] > 56) d_valid = 0;
        if ((i + 1) % 12 == 0) printf("\n");
    }

    printf("\nVerification:\n");
    printf("1. First 24 subkey bits come exclusively from C (1-28): %s\n", c_valid ? "CONFIRMED" : "FAILED");
    printf("2. Second 24 subkey bits come exclusively from D (29-56): %s\n", d_valid ? "CONFIRMED" : "FAILED");
    printf("3. C and D are disjoint subsets of 28 bits each from the 56-bit key.\n");

    return 0;
}
