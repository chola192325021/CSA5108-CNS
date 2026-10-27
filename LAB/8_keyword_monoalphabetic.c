#include <stdio.h>
#include <ctype.h>
#include <string.h>

void generateKeyMap(char *keyword, char *keyMap) {
    int vis[26] = {0};
    int len = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        if (isalpha(keyword[i])) {
            char ch = toupper(keyword[i]);
            if (!vis[ch - 'A']) {
                vis[ch - 'A'] = 1;
                keyMap[len++] = ch;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!vis[i]) {
            keyMap[len++] = 'A' + i;
        }
    }
    keyMap[26] = '\0';
}

void encrypt(char *str, char *keyMap) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            str[i] = keyMap[str[i] - 'A'];
        } else if (islower(str[i])) {
            str[i] = tolower(keyMap[str[i] - 'a']);
        }
    }
}

void decrypt(char *str, char *keyMap) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            char ch = toupper(str[i]);
            for (int j = 0; j < 26; j++) {
                if (keyMap[j] == ch) {
                    str[i] = isupper(str[i]) ? ('A' + j) : ('a' + j);
                    break;
                }
            }
        }
    }
}

int main() {
    char keyword[50], keyMap[27], str[100];

    printf("Enter keyword: ");
    scanf("%s", keyword);
    getchar();

    generateKeyMap(keyword, keyMap);

    printf("Plain alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher sequence: %s\n\n", keyMap);

    printf("Enter plaintext: ");
    scanf("%[^\n]", str);

    encrypt(str, keyMap);
    printf("Encrypted: %s\n", str);

    decrypt(str, keyMap);
    printf("Decrypted: %s\n", str);

    return 0;
}
