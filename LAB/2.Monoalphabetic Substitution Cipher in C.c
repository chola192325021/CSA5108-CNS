#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plaintext[100];
    char key[27];
    char ciphertext[100];
    int i, index;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the substitution key (26 unique letters): ");
    scanf("%26s", key);

    /* Check whether key contains 26 letters */
    if (strlen(key) != 26)
    {
        printf("Invalid key! The key must contain exactly 26 letters.\n");
        return 0;
    }

    /* Encrypt the plaintext */
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isupper(plaintext[i]))
        {
            index = plaintext[i] - 'A';
            ciphertext[i] = toupper(key[index]);
        }
        else if (islower(plaintext[i]))
        {
            index = plaintext[i] - 'a';
            ciphertext[i] = tolower(key[index]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}
