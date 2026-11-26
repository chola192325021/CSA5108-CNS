#include <stdio.h>
#include <string.h>

void pad(unsigned char *in, int inLen, unsigned char *out, int *outLen, int blockSize) {
    memcpy(out, in, inLen);
    out[inLen] = 0x80;
    int padZeros = (blockSize - ((inLen + 1) % blockSize)) % blockSize;
    for (int i = 1; i <= padZeros; i++) out[inLen + i] = 0x00;
    *outLen = inLen + 1 + padZeros;
}

int unpad(unsigned char *buf, int len) {
    int i = len - 1;
    while (i >= 0 && buf[i] == 0x00) i--;
    if (i >= 0 && buf[i] == 0x80) return i;
    return len;
}

void printHex(const char *label, unsigned char *b, int len) {
    printf("%-20s (%2d bytes): ", label, len);
    for (int i = 0; i < len; i++) printf("%02X ", b[i]);
    printf("\n");
}

int main() {
    int blockSize = 8;

    unsigned char msg1[] = "HELLO";
    int len1 = strlen((char *)msg1);
    unsigned char padded1[32];
    int pLen1;

    pad(msg1, len1, padded1, &pLen1, blockSize);
    printf("Case 1: Message length NOT a multiple of block size\n");
    printHex("Original", msg1, len1);
    printHex("Padded", padded1, pLen1);
    int unpaddedLen1 = unpad(padded1, pLen1);
    printHex("Unpadded", padded1, unpaddedLen1);

    unsigned char msg2[] = "12345678";
    int len2 = strlen((char *)msg2);
    unsigned char padded2[32];
    int pLen2;

    pad(msg2, len2, padded2, &pLen2, blockSize);
    printf("\nCase 2: Message length ALREADY a multiple of block size (extra block added)\n");
    printHex("Original", msg2, len2);
    printHex("Padded", padded2, pLen2);
    int unpaddedLen2 = unpad(padded2, pLen2);
    printHex("Unpadded", padded2, unpaddedLen2);

    printf("\nMotivation for always adding a padding block:\n");
    printf("Without an unconditional padding block, the receiver cannot distinguish\n");
    printf("whether trailing bytes in a full block are user data or padding.\n");
    printf("Always appending padding guarantees unambiguous unpadding for all messages.\n");

    return 0;
}
