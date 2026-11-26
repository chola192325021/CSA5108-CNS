#include <stdio.h>
#include <string.h>

void pad(const unsigned char *in, int inLen, unsigned char *out, int *outLen, int bSize) {
    memcpy(out, in, inLen);
    out[inLen] = 0x80;
    int padZeros = (bSize - ((inLen + 1) % bSize)) % bSize;
    for (int i = 1; i <= padZeros; i++) out[inLen + i] = 0x00;
    *outLen = inLen + 1 + padZeros;
}

int unpad(const unsigned char *buf, int len) {
    int i = len - 1;
    while (i >= 0 && buf[i] == 0x00) i--;
    if (i >= 0 && buf[i] == 0x80) return i;
    return len;
}

void printData(const char *tag, const unsigned char *d, int len) {
    printf("%-20s (%2d bytes): ", tag, len);
    for (int i = 0; i < len; i++) printf("%02X ", d[i]);
    printf("\n");
}

int main() {
    int bSize = 8;

    unsigned char msgA[] = "NETWORKS";
    int lenA = 8;
    unsigned char padA[32];
    int outLenA;

    pad(msgA, lenA, padA, &outLenA, bSize);
    printf("Message Already A Complete Block (8 bytes):\n");
    printData("Original Message", msgA, lenA);
    printData("Padded Message", padA, outLenA);
    printData("Unpadded Message", padA, unpad(padA, outLenA));

    unsigned char msgB[] = "DATA";
    int lenB = 4;
    unsigned char padB[32];
    int outLenB;

    pad(msgB, lenB, padB, &outLenB, bSize);
    printf("\nIncomplete Message Block (4 bytes):\n");
    printData("Original Message", msgB, lenB);
    printData("Padded Message", padB, outLenB);
    printData("Unpadded Message", padB, unpad(padB, outLenB));

    printf("\nMotivation for adding padding even when not needed:\n");
    printf("If an already complete block is not padded, the receiver cannot distinguish\n");
    printf("between genuine message bytes and padding bits (e.g. if message ends with 0x80).\n");
    printf("Adding an unconditional padding block ensures uniform, unambiguous unpadding.\n");

    return 0;
}
