#include <stdio.h>

int main() {
    int encShifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    int decShifts[16] = {0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    printf("DES Encryption vs Decryption Key Shift Schedule:\n\n");
    printf("%-7s %-12s %-10s %-7s %-13s %-10s\n",
           "Round", "Enc Subkey", "Left Shift", "Round", "Dec Subkey", "Right Shift");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < 16; i++) {
        printf(" %-6d  K%-10d %-10d  %-6d  K%-11d %-10d\n",
               i + 1, i + 1, encShifts[i],
               i + 1, 16 - i, decShifts[i]);
    }

    printf("\nDecryption Key Generation Principle:\n");
    printf("1. After round 16 of encryption, C16=C0 and D16=D0 (sum of shifts = 28).\n");
    printf("2. For K16, no shift is applied (0 shifts) to C16 and D16.\n");
    printf("3. For subsequent rounds, right circular shifts reverse the encryption process.\n");

    return 0;
}
