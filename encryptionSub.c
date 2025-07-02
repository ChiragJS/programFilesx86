#include <stdio.h>
#include <string.h>
#include <ctype.h>
    int
    main()
{
    char seq[36] = "qwertyuiopasdfghjklzxcvbnm1234567890";
    char data[50];
    char encoded[50];
    int i, len;
    printf("\nEnter data: ");
    fgets(data, sizeof(data), stdin);
    len = strlen(data);
    for (i = 0; i < len; i++)
    {
        if (isupper(data[i]))
            encoded[i] = toupper(seq[data[i] - 'A']);
        else if (islower(data[i]))
            encoded[i] = seq[data[i] - 'a'];
        else if (isdigit(data[i]))
            encoded[i] = seq[data[i] - '0' + 26];
        else
            encoded[i] = data[i];
    }
    encoded[len] = '\0';
    printf("\nEncoded string is: %s\n", encoded);
}
