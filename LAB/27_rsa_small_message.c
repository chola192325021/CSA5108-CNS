#include <stdio.h>
#include <string.h>

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    long long n = 3599, e = 31;
    char msg[] = "HELLO";
    int len = strlen(msg);
    long long cipher[100];

    printf("Public Key: n = %lld, e = %lld\n", n, e);
    printf("Original Message: %s\n", msg);
    printf("Ciphertext blocks: ");
    for (int i = 0; i < len; i++) {
        long long m = msg[i] - 'A';
        cipher[i] = modExp(m, e, n);
        printf("%lld ", cipher[i]);
    }
    printf("\n\n");

    long long dict[26];
    for (int i = 0; i < 26; i++) {
        dict[i] = modExp(i, e, n);
    }

    printf("--- ATTACK: PRECOMPUTED CODEBOOK / DICTIONARY ATTACK ---\n");
    printf("Decrypted without private key: ");
    for (int i = 0; i < len; i++) {
        for (int m = 0; m < 26; m++) {
            if (cipher[i] == dict[m]) {
                printf("%c", m + 'A');
                break;
            }
        }
    }
    printf("\n\nConclusion:\n");
    printf("This method is completely INSECURE.\n");
    printf("Since the plaintext space has only 26 values (0-25), an attacker can\n");
    printf("precompute C = m^e mod n for all 26 letters in milliseconds and invert\n");
    printf("every ciphertext block via direct lookup, without factoring n.\n");

    return 0;
}
