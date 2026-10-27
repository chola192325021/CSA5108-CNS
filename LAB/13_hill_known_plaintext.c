#include <stdio.h>

int mod(int x) { int r = x % 26; return r < 0 ? r + 26 : r; }

int main() {
    int K[2][2] = {{9, 4}, {5, 7}};
    int P[2][2] = {{5, 17}, {8, 3}};
    int C[2][2], invP[2][2], recK[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            C[i][j] = mod(P[i][0] * K[0][j] + P[i][1] * K[1][j]);

    int det = mod(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int invDet = 1;
    while (mod(det * invDet) != 1) invDet++;

    invP[0][0] = mod(invDet * P[1][1]);
    invP[0][1] = mod(invDet * -P[0][1]);
    invP[1][0] = mod(invDet * -P[1][0]);
    invP[1][1] = mod(invDet * P[0][0]);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            recK[i][j] = mod(invP[i][0] * C[0][j] + invP[i][1] * C[1][j]);

    printf("Original Secret Key:        [[%d, %d], [%d, %d]]\n", K[0][0], K[0][1], K[1][0], K[1][1]);
    printf("KPA Recovered Key (P^-1*C): [[%d, %d], [%d, %d]]\n\n", recK[0][0], recK[0][1], recK[1][0], recK[1][1]);

    int chosenP[2][2] = {{1, 0}, {0, 1}}, chosenC[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            chosenC[i][j] = mod(chosenP[i][0] * K[0][j] + chosenP[i][1] * K[1][j]);

    printf("CPA Chosen Plaintext:       I = [[1, 0], [0, 1]]\n");
    printf("CPA Revealed Key (C=I*K):   [[%d, %d], [%d, %d]]\n", chosenC[0][0], chosenC[0][1], chosenC[1][0], chosenC[1][1]);
    return 0;
}
