#include <stdio.h>
#include <ctype.h>
#include <string.h>

int gcd(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int modInverse(int a) {
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

int main() {
    char cipher[500];
    int p1 = 'E' - 'A', c1 = 'B' - 'A';
    int p2 = 'T' - 'A', c2 = 'U' - 'A';
    int keyA = -1, keyB = -1;

    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) {
            for (int b = 0; b < 26; b++) {
                if ((a * p1 + b) % 26 == c1 && (a * p2 + b) % 26 == c2) {
                    keyA = a;
                    keyB = b;
                    break;
                }
            }
        }
    }

    printf("Found Key: a = %d, b = %d\n", keyA, keyB);

    printf("Enter ciphertext (or press enter for default 'BU'): ");
    if (fgets(cipher, sizeof(cipher), stdin) != NULL) {
        size_t len = strlen(cipher);
        if (len > 0 && cipher[len - 1] == '\n') cipher[len - 1] = '\0';
    }

    if (strlen(cipher) == 0) {
        strcpy(cipher, "BU");
    }

    int a_inv = modInverse(keyA);
    printf("Decrypted text: ");
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isupper(cipher[i])) {
            int p = (a_inv * (cipher[i] - 'A' - keyB + 26)) % 26;
            printf("%c", (p + 26) % 26 + 'A');
        } else if (islower(cipher[i])) {
            int p = (a_inv * (cipher[i] - 'a' - keyB + 26)) % 26;
            printf("%c", (p + 26) % 26 + 'a');
        } else {
            printf("%c", cipher[i]);
        }
    }
    printf("\n");

    return 0;
}
