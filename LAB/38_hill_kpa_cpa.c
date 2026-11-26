#include <stdio.h>

int mod(int x) { int r = x % 26; return r < 0 ? r + 26 : r; }

int main() {
    int secretKey[2][2] = {{9, 4}, {5, 7}};
    printf("Secret Key K: [[%d, %d], [%d, %d]]\n\n", secretKey[0][0], secretKey[0][1], secretKey[1][0], secretKey[1][1]);

    printf("--- 1. KNOWN PLAINTEXT ATTACK (KPA) ---\n");
    int P[2][2] = {{5, 17}, {8, 3}};
    int C[2][2], invP[2][2], recK[2][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            C[i][j] = mod(P[i][0] * secretKey[0][j] + P[i][1] * secretKey[1][j]);

    printf("Known Plaintext P: [[%d, %d], [%d, %d]]\n", P[0][0], P[0][1], P[1][0], P[1][1]);
    printf("Intercepted C:     [[%d, %d], [%d, %d]]\n", C[0][0], C[0][1], C[1][0], C[1][1]);

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

    printf("Recovered Key (P^-1 * C): [[%d, %d], [%d, %d]]\n\n", recK[0][0], recK[0][1], recK[1][0], recK[1][1]);

    printf("--- 2. CHOSEN PLAINTEXT ATTACK (CPA) ---\n");
    int chosenP[2][2] = {{1, 0}, {0, 1}}, chosenC[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            chosenC[i][j] = mod(chosenP[i][0] * secretKey[0][j] + chosenP[i][1] * secretKey[1][j]);

    printf("Chosen Plaintext (Identity Matrix): [[1, 0], [0, 1]]\n");
    printf("Resulting Ciphertext directly gives K: [[%d, %d], [%d, %d]]\n", chosenC[0][0], chosenC[0][1], chosenC[1][0], chosenC[1][1]);

    return 0;
}
