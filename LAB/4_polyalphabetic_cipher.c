#include <stdio.h>
#include <ctype.h>
#include <string.h>

void polyEncrypt(char *str, char *key) {
    int kLen = strlen(key);
    for (int i = 0, j = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            int shift = toupper(key[j % kLen]) - 'A';
            str[i] = (str[i] - 'A' + shift) % 26 + 'A';
            j++;
        } else if (islower(str[i])) {
            int shift = tolower(key[j % kLen]) - 'a';
            str[i] = (str[i] - 'a' + shift) % 26 + 'a';
            j++;
        }
    }
}

void polyDecrypt(char *str, char *key) {
    int kLen = strlen(key);
    for (int i = 0, j = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            int shift = toupper(key[j % kLen]) - 'A';
            str[i] = (str[i] - 'A' - shift + 26) % 26 + 'A';
            j++;
        } else if (islower(str[i])) {
            int shift = tolower(key[j % kLen]) - 'a';
            str[i] = (str[i] - 'a' - shift + 26) % 26 + 'a';
            j++;
        }
    }
}

int main() {
    char str[100], key[50];

    printf("Enter key: ");
    scanf("%s", key);
    getchar();

    printf("Enter plaintext: ");
    scanf("%[^\n]", str);

    polyEncrypt(str, key);
    printf("Encrypted: %s\n", str);

    polyDecrypt(str, key);
    printf("Decrypted: %s\n", str);

    return 0;
}
