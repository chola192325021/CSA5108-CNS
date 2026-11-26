#include <stdio.h>

void genSubkeys64(unsigned long long L, unsigned long long *K1, unsigned long long *K2) {
    unsigned long long const64 = 0x1B;
    int msbL = (L >> 63) & 1;
    *K1 = (L << 1) ^ (msbL ? const64 : 0);

    int msbK1 = (*K1 >> 63) & 1;
    *K2 = (*K1 << 1) ^ (msbK1 ? const64 : 0);
}

void shiftLeft128(unsigned long long *hi, unsigned long long *lo) {
    int carry = (*lo >> 63) & 1;
    *lo = *lo << 1;
    *hi = (*hi << 1) | carry;
}

void genSubkeys128(unsigned long long L_hi, unsigned long long L_lo,
                   unsigned long long *K1_hi, unsigned long long *K1_lo,
                   unsigned long long *K2_hi, unsigned long long *K2_lo) {
    unsigned long long const128 = 0x87;
    int msbL = (L_hi >> 63) & 1;

    *K1_hi = L_hi; *K1_lo = L_lo;
    shiftLeft128(K1_hi, K1_lo);
    if (msbL) *K1_lo ^= const128;

    int msbK1 = (*K1_hi >> 63) & 1;
    *K2_hi = *K1_hi; *K2_lo = *K1_lo;
    shiftLeft128(K2_hi, K2_lo);
    if (msbK1) *K2_lo ^= const128;
}

int main() {
    unsigned long long L64 = 0x8A123456789ABCDEULL;
    unsigned long long K1_64, K2_64;
    genSubkeys64(L64, &K1_64, &K2_64);

    printf("--- 64-BIT BLOCK CMAC ---\n");
    printf("L:  0x%016llX\nK1: 0x%016llX\nK2: 0x%016llX\n\n", L64, K1_64, K2_64);

    unsigned long long L128_hi = 0x9B123456789ABCDEULL, L128_lo = 0xFEDCBA9876543210ULL;
    unsigned long long K1_hi, K1_lo, K2_hi, K2_lo;
    genSubkeys128(L128_hi, L128_lo, &K1_hi, &K1_lo, &K2_hi, &K2_lo);

    printf("--- 128-BIT BLOCK CMAC ---\n");
    printf("L:  0x%016llX%016llX\n", L128_hi, L128_lo);
    printf("K1: 0x%016llX%016llX\n", K1_hi, K1_lo);
    printf("K2: 0x%016llX%016llX\n\n", K2_hi, K2_lo);

    printf("Answers:\n");
    printf("a. Constants needed:\n");
    printf("   - For 64-bit block:  Const = 0x1B (from x^64 + x^4 + x^3 + x + 1)\n");
    printf("   - For 128-bit block: Const = 0x87 (from x^128 + x^7 + x^2 + x + 1)\n\n");
    printf("b. Left shift and XOR operation:\n");
    printf("   Left shift corresponds to multiplying by x (or 2) in GF(2^b).\n");
    printf("   If MSB is 1 (overflowing bit b), XORing the constant performs\n");
    printf("   modular reduction by the irreducible polynomial of the Galois Field.\n");

    return 0;
}
