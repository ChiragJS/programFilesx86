#include <stdio.h>
#include <stdlib.h>

#define MAX_MSG    30
#define DEGREE     16
#define MAX_FRAME  (MAX_MSG + DEGREE)

int mod2add(int, int);
int getnext(int *, int, int);
int result[MAX_FRAME];

void calc_crc(int length)
{
    int ccitt[DEGREE+1] = { 1,0,0,0, 1,0,0,0, 0,0,0,1, 0,0,0,0, 1 };
    int pos = 0;

    while (pos <= length - DEGREE - 1) {
        if (result[pos] == 1) {
            for (int i = 0; i < DEGREE + 1; ++i) {
                result[pos + i] = mod2add(result[pos + i], ccitt[i]);
            }
        }
        pos = getnext(result, pos + 1, length);
        if (pos < 0 || pos > length - DEGREE - 1)
            break;
    }
}

int getnext(int array[], int start, int length)
{
    for (int i = start; i < length; ++i) {
        if (array[i] == 1)
            return i;
    }
    return -1;
}

int mod2add(int x, int y)
{
    return x ^ y;
}

int main()
{
    int array[MAX_FRAME];
    int length = 0;
    char ch;

    printf("Enter the data (message) stream (up to %d bits), press Enter when done:\n", MAX_MSG);
    do {
        if (length >= MAX_MSG)
            break;
        if (scanf("%c", &ch) != 1)
            break;
        if (ch == '\n')
            break;
        if (ch == '0' || ch == '1')
            array[length++] = ch - '0';
    } while (1);

    // Append DEGREE zeros
    for (int i = 0; i < DEGREE; ++i)
        array[length + i] = 0;
    length += DEGREE;

    // Copy into result for CRC calc
    for (int i = 0; i < length; ++i)
        result[i] = array[i];

    calc_crc(length);

    printf("\nThe transmitted frame is: ");
    for (int i = 0; i < length - DEGREE; ++i)
        printf("%d", array[i]);
    for (int i = length - DEGREE; i < length; ++i)
        printf("%d", result[i]);
    printf("\n\n");

    // Decoding/checking
    printf("Enter the received frame for CRC check (%d bits), press Enter when done:\n", length);
    int recv_len = 0;
    do {
        if (recv_len >= length)
            break;
        if (scanf("%c", &ch) != 1)
            break;
        if (ch == '\n')
            break;
        if (ch == '0' || ch == '1')
            array[recv_len++] = ch - '0';
    } while (1);

    if (recv_len != length) {
        fprintf(stderr, "Error: expected %d bits, got %d bits.\n", length, recv_len);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < length; ++i)
        result[i] = array[i];
    calc_crc(length);

    printf("Calculated checksum: ");
    for (int i = length - DEGREE; i < length; ++i)
        printf("%d", result[i]);
    printf("\n");

    // Check if CRC remainder is zero
    int error = 0;
    for (int i = length - DEGREE; i < length; ++i) {
        if (result[i] != 0) {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected in received frame.\n");
    else
        printf("No error detected.\n");

    return 0;
}
