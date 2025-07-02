#include <stdio.h>
#include <string.h>
    int
    main()
{
    char data[100];
    char wrd[] = "MEGABUCK";
    char cipher[20][8];
    int seq[8];
    int i, j, cnt, c;

    for (i = 0; i < strlen(wrd); i++)
    {
        cnt = 0;
        for (j = 0; j < strlen(wrd); j++)
        {
            if (wrd[i] > wrd[j])
                ++cnt;
        }
        seq[i] = cnt;
    }

    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove newline

    cnt = strlen(data);

    if (cnt % strlen(wrd) != 0)
    {
        printf("Error: Invalid Input length (must be multiple of %lu)\n", strlen(wrd));
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            for (c = 0; c < 8; c++)
            {
                if (seq[c] == i)
                    break;
            }

            for (j = 0; j < cnt / strlen(wrd); j++)
            {
                cipher[j][c] = data[i * (cnt / strlen(wrd)) + j];
            }
        }
        printf("Decrypted data: ");
        for (i = 0; i < cnt; i++)
        {
            if (cipher[i / strlen(wrd)][i % strlen(wrd)] != '.')
            {
                printf("%c", cipher[i / strlen(wrd)][i % strlen(wrd)]);
            }
        }
        printf("\n");
    }

    return 0;
}