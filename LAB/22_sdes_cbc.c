#include <stdio.h>

int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[]  = {6, 3, 7, 4, 8, 5, 10, 9};
int IP[]  = {2, 6, 3, 1, 4, 8, 5, 7};
int IPI[] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[]  = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[]  = {2, 4, 3, 1};

int S0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int S1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

int perm(int in, int inBits, int *p, int outBits) {
    int res = 0;
    for (int i = 0; i < outBits; i++)
        res = (res << 1) | ((in >> (inBits - p[i])) & 1);
    return res;
}

int leftShift(int val, int n, int bits) {
    int mask = (1 << bits) - 1;
    return ((val << n) | (val >> (bits - n))) & mask;
}

void genKeys(int key, int *k1, int *k2) {
    int p10 = perm(key, 10, P10, 10);
    int l = leftShift((p10 >> 5) & 31, 1, 5);
    int r = leftShift(p10 & 31, 1, 5);
    *k1 = perm((l << 5) | r, 10, P8, 8);

    l = leftShift(l, 2, 5);
    r = leftShift(r, 2, 5);
    *k2 = perm((l << 5) | r, 10, P8, 8);
}

int fK(int r, int k) {
    int ep = perm(r, 4, EP, 8) ^ k;
    int l = (ep >> 4) & 15, rt = ep & 15;
    int row0 = ((l >> 3) & 1) * 2 + (l & 1), col0 = ((l >> 2) & 1) * 2 + ((l >> 1) & 1);
    int row1 = ((rt >> 3) & 1) * 2 + (rt & 1), col1 = ((rt >> 2) & 1) * 2 + ((rt >> 1) & 1);
    int s = (S0[row0][col0] << 2) | S1[row1][col1];
    return perm(s, 4, P4, 4);
}

int sdes(int b, int k1, int k2) {
    int ip = perm(b, 8, IP, 8);
    int l = (ip >> 4) & 15, r = ip & 15;
    int l1 = r, r1 = l ^ fK(r, k1);
    int l2 = l1 ^ fK(r1, k2), r2 = r1;
    return perm((l2 << 4) | r2, 8, IPI, 8);
}

void printBin(int val, int n) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

int main() {
    int key = 0x1FD;
    int iv  = 0xAA;
    int p[2] = {0x01, 0x23};
    int c[2], d[2];
    int k1, k2;

    genKeys(key, &k1, &k2);

    int prev = iv;
    for (int i = 0; i < 2; i++) {
        c[i] = sdes(p[i] ^ prev, k1, k2);
        prev = c[i];
    }

    printf("S-DES CBC Encryption:\n");
    printf("Plaintext:  "); printBin(p[0], 8); printf(" "); printBin(p[1], 8); printf("\n");
    printf("Ciphertext: "); printBin(c[0], 8); printf(" "); printBin(c[1], 8); printf("\n\n");

    prev = iv;
    for (int i = 0; i < 2; i++) {
        d[i] = sdes(c[i], k2, k1) ^ prev;
        prev = c[i];
    }

    printf("S-DES CBC Decryption:\n");
    printf("Recovered:  "); printBin(d[0], 8); printf(" "); printBin(d[1], 8); printf("\n");

    return 0;
}
