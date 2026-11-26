#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encryptOTP(const char *in, const int *key, char *out) {
    int ki = 0;
    for (int i = 0; in[i]; i++) {
        if (isupper(in[i])) {
            out[i] = ((in[i] - 'A' + key[ki++]) % 26) + 'A';
        } else if (islower(in[i])) {
            out[i] = ((in[i] - 'a' + key[ki++]) % 26) + 'a';
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

void decryptOTP(const char *in, const int *key, char *out) {
    int ki = 0;
    for (int i = 0; in[i]; i++) {
        if (isupper(in[i])) {
            out[i] = ((in[i] - 'A' - key[ki++] + 26) % 26) + 'A';
        } else if (islower(in[i])) {
            out[i] = ((in[i] - 'a' - key[ki++] + 26) % 26) + 'a';
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

int main() {
    char plain[] = "ONETIME PAD VIGENERE";
    int len = strlen(plain);
    int key[100];
    char cipher[100], decrypted[100];

    int letterCount = 0;
    for (int i = 0; i < len; i++)
        if (isalpha(plain[i])) letterCount++;

    int sampleKeys[] = {3, 19, 5, 11, 23, 7, 2, 14, 21, 8, 17, 4, 12, 1, 9, 16, 20, 25};
    for (int i = 0; i < letterCount; i++) {
        key[i] = sampleKeys[i % 18];
    }

    encryptOTP(plain, key, cipher);
    decryptOTP(cipher, key, decrypted);

    printf("Plaintext:  %s\n", plain);
    printf("Key Stream: ");
    for (int i = 0; i < letterCount; i++) printf("%d ", key[i]);
    printf("\n");
    printf("Ciphertext: %s\n", cipher);
    printf("Decrypted:  %s\n", decrypted);

    return 0;
}
