#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char seq[36] = "qwertyuiopasdfghjklzxcvbnm1234567890";
    char data[100];
    char decoded[100];
    int i, j, len, present;

    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    // Remove newline character
    data[strcspn(data, "\n")] = '\0';

    len = strlen(data);

    for (i = 0; i < len; i++)
    {
        present = 0;

        for (j = 0; j < 36; ++j)
        {
            if (seq[j] == tolower(data[i]))
            {
                if (j < 26)
                { // It's a letter
                    if (isupper(data[i]))
                        decoded[i] = 'A' + j;
                    else
                        decoded[i] = 'a' + j;
                }
                else
                { // It's a digit
                    decoded[i] = '0' + (j - 26);
                }
                present = 1;
                break;
            }
        }

        if (!present)
            decoded[i] = data[i]; // Copy non-encoded characters as-is
    }

    decoded[len] = '\0';
    printf("Decoded string is: %s\n", decoded);

    return 0;
}