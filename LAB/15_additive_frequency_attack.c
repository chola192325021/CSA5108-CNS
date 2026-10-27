#include <stdio.h>
#include <string.h>
#include <ctype.h>

const double f[26] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.1, 2.0, 0.1};

int main() {
    char cipher[300] = "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj", in[300];
    int n = 10, keys[26];
    double scores[26];

    printf("Enter ciphertext: ");
    if (fgets(in, sizeof(in), stdin) && in[0] != '\n') {
        in[strcspn(in, "\n")] = '\0';
        strcpy(cipher, in);
    }
    printf("Enter number of top plaintexts: ");
    if (scanf("%d", &n) != 1 || n < 1) n = 10;

    for (int k = 0; k < 26; k++) {
        keys[k] = k;
        scores[k] = 0;
        for (int i = 0; cipher[i]; i++)
            if (isalpha(cipher[i]))
                scores[k] += f[(toupper(cipher[i]) - 'A' - k + 26) % 26];
    }

    for (int i = 0; i < 25; i++)
        for (int j = i + 1; j < 26; j++)
            if (scores[j] > scores[i]) {
                double ts = scores[i]; scores[i] = scores[j]; scores[j] = ts;
                int tk = keys[i]; keys[i] = keys[j]; keys[j] = tk;
            }

    printf("\nTop %d Plaintexts:\n", n);
    for (int i = 0; i < n && i < 26; i++) {
        printf("Key %2d (Score %6.1f): ", keys[i], scores[i]);
        for (int j = 0; cipher[j]; j++) {
            if (isupper(cipher[j])) printf("%c", (cipher[j] - 'A' - keys[i] + 26) % 26 + 'A');
            else if (islower(cipher[j])) printf("%c", (cipher[j] - 'a' - keys[i] + 26) % 26 + 'a');
            else printf("%c", cipher[j]);
        }
        printf("\n");
    }
    return 0;
}
