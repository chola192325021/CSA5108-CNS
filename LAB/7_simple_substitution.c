#include <stdio.h>
#include <string.h>

void decode(const char *cipher) {
    for (int i = 0; cipher[i] != '\0'; ) {
        if (strncmp(&cipher[i], "‡", strlen("‡")) == 0) { printf("o"); i += strlen("‡"); }
        else if (strncmp(&cipher[i], "†", strlen("†")) == 0) { printf("d"); i += strlen("†"); }
        else if (strncmp(&cipher[i], "¶", strlen("¶")) == 0) { printf("v"); i += strlen("¶"); }
        else if (strncmp(&cipher[i], "—", strlen("—")) == 0) { printf("b"); i += strlen("—"); }
        else {
            char c = cipher[i];
            if (c == '5') printf("a");
            else if (c == '2') printf("b");
            else if (c == '8') printf("e");
            else if (c == '1') printf("f");
            else if (c == '3') printf("g");
            else if (c == '4') printf("h");
            else if (c == '6') printf("i");
            else if (c == '0') printf("l");
            else if (c == '9') printf("m");
            else if (c == '*') printf("n");
            else if (c == '.') printf("p");
            else if (c == '(') printf("r");
            else if (c == ')') printf("s");
            else if (c == ';') printf("t");
            else if (c == '?') printf("u");
            else if (c == ']') printf("w");
            else if (c == ':') printf("y");
            else printf("%c", c);
            i++;
        }
    }
    printf("\n");
}

int main() {
    char cipher[] = 
        "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    printf("Ciphertext:\n%s\n\n", cipher);
    printf("Decrypted text:\n");
    decode(cipher);

    return 0;
}
