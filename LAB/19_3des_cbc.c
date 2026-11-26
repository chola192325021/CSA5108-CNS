#include <stdio.h>
#include <string.h>

void blockEncrypt(unsigned char *out, const unsigned char *in, unsigned char k1, unsigned char k2, unsigned char k3) {
    for (int i = 0; i < 8; i++) {
        unsigned char t = in[i] ^ k1;
        t = t ^ k2;
        out[i] = t ^ k3;
    }
}

int main() {
    unsigned char iv[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    unsigned char k1 = 0xA5, k2 = 0x5A, k3 = 0xF0;
    char text[] = "Hello3DESCBCMode";
    unsigned char c[24], prev[8];

    memcpy(prev, iv, 8);
    int numBlocks = strlen(text) / 8;

    printf("Plaintext:  %s\n", text);
    printf("IV:         ");
    for (int i = 0; i < 8; i++) printf("%02X ", iv[i]);
    printf("\n\nCBC Encryption (3DES EDE):\n");

    for (int b = 0; b < numBlocks; b++) {
        unsigned char xorBlock[8];
        for (int i = 0; i < 8; i++)
            xorBlock[i] = (unsigned char)text[b * 8 + i] ^ prev[i];

        blockEncrypt(&c[b * 8], xorBlock, k1, k2, k3);
        memcpy(prev, &c[b * 8], 8);

        printf("Block %d Cipher: ", b + 1);
        for (int i = 0; i < 8; i++) printf("%02X ", c[b * 8 + i]);
        printf("\n");
    }

    printf("\nComparison & Decisions:\n");
    printf("a. For Security: Choose 3-key 3DES (168-bit key) or AES-256.\n");
    printf("   Reason: Resists meet-in-the-middle attacks and provides full cryptographic strength.\n\n");
    printf("b. For Performance: Choose 2-key 3DES (or AES).\n");
    printf("   Reason: Requires less key management overhead; AES has native hardware acceleration.\n");

    return 0;
}
