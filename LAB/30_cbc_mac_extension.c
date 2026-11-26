#include <stdio.h>

unsigned char blockCipher(unsigned char in, unsigned char key) {
    return (in * 13 + key) ^ 0x5C;
}

unsigned char cbcMac(const unsigned char *blocks, int n, unsigned char key) {
    unsigned char state = 0;
    for (int i = 0; i < n; i++) {
        state = blockCipher(blocks[i] ^ state, key);
    }
    return state;
}

int main() {
    unsigned char key = 0x7A;
    unsigned char X = 0x42;

    unsigned char T = cbcMac(&X, 1, key);

    printf("Secret Key K: 0x%02X\n", key);
    printf("One-block message X: 0x%02X\n", X);
    printf("Computed Tag T = MAC(K, X) = 0x%02X\n\n", T);

    unsigned char twoBlockMsg[2];
    twoBlockMsg[0] = X;
    twoBlockMsg[1] = X ^ T;

    printf("Constructing Two-block message: X || (X ^ T)\n");
    printf("Block 1 = 0x%02X\n", twoBlockMsg[0]);
    printf("Block 2 = 0x%02X ^ 0x%02X = 0x%02X\n\n", X, T, twoBlockMsg[1]);

    unsigned char forgedT = cbcMac(twoBlockMsg, 2, key);

    printf("CBC-MAC Calculation on Two-block Message:\n");
    printf("Stage 1: C1 = E(X ^ 0) = T = 0x%02X\n", T);
    printf("Stage 2: C2 = E((X ^ T) ^ C1) = E(X ^ T ^ T) = E(X) = 0x%02X\n", forgedT);
    printf("Resulting Tag = 0x%02X\n\n", forgedT);

    printf("Verification:\n");
    printf("T == forgedT? %s\n\n", (T == forgedT) ? "YES (FORGERY CONFIRMED)" : "NO");

    printf("Conclusion:\n");
    printf("For basic CBC-MAC with variable-length messages, an adversary knowing\n");
    printf("T = MAC(K, X) immediately knows MAC(K, X || (X ^ T)) = T without knowing K.\n");

    return 0;
}
