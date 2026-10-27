#include <stdio.h>

int main() {
    char p1[] = "sendmoremoney", p2[] = "cashnotneeded", c[20];
    int k1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}, k2[20];
    int len = 13;

    for (int i = 0; i < len; i++)
        c[i] = ((p1[i] - 'a' + k1[i]) % 26) + 'A';
    c[len] = '\0';

    printf("Ciphertext: %s\nNew Key:    ", c);
    for (int i = 0; i < len; i++) {
        k2[i] = (c[i] - 'A' - (p2[i] - 'a') + 26) % 26;
        printf("%d ", k2[i]);
    }

    printf("\nDecrypted:  ");
    for (int i = 0; i < len; i++)
        printf("%c", ((c[i] - 'A' - k2[i] + 26) % 26) + 'a');
    printf("\n");
    return 0;
}
