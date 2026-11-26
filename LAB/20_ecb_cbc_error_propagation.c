#include <stdio.h>
#include <string.h>

unsigned char enc(unsigned char p) { return (p + 13) % 256; }
unsigned char dec(unsigned char c) { return (c - 13 + 256) % 256; }

int main() {
    unsigned char p[4] = {'A', 'B', 'C', 'D'};
    unsigned char iv = 0xAA;
    unsigned char ecb_c[4], cbc_c[4];

    for (int i = 0; i < 4; i++) ecb_c[i] = enc(p[i]);

    unsigned char prev = iv;
    for (int i = 0; i < 4; i++) {
        cbc_c[i] = enc(p[i] ^ prev);
        prev = cbc_c[i];
    }

    printf("Original Plaintext: P1='%c', P2='%c', P3='%c', P4='%c'\n\n", p[0], p[1], p[2], p[3]);

    printf("--- TRANSMISSION ERROR IN C1 ---\n");
    unsigned char bad_ecb_c[4], bad_cbc_c[4];
    memcpy(bad_ecb_c, ecb_c, 4);
    memcpy(bad_cbc_c, cbc_c, 4);
    bad_ecb_c[0] ^= 0x01;
    bad_cbc_c[0] ^= 0x01;

    printf("ECB Decryption with corrupted C1:\n");
    for (int i = 0; i < 4; i++)
        printf("P%d: '%c' (%s)\n", i + 1, dec(bad_ecb_c[i]), (i == 0) ? "Corrupted" : "Intact");

    printf("\nCBC Decryption with corrupted C1:\n");
    prev = iv;
    for (int i = 0; i < 4; i++) {
        unsigned char rec = dec(bad_cbc_c[i]) ^ prev;
        prev = bad_cbc_c[i];
        printf("P%d: '%c' (%s)\n", i + 1, rec, (i <= 1) ? "Corrupted" : "Intact");
    }

    printf("\na. Are any blocks beyond P2 affected in CBC transmission error?\n");
    printf("   Answer: NO. P3, P4, ... are completely intact (self-synchronizing).\n\n");

    printf("b. Source bit error in P1 before encryption:\n");
    printf("   1. Ciphertext propagation: Propagates through ALL subsequent ciphertext blocks (C1 to Cn).\n");
    printf("   2. Effect at receiver: Since decryption inverts the chain, only P1 contains the error;\n");
    printf("      all subsequent blocks (P2 to Pn) are recovered correctly.\n");

    return 0;
}
