#include <stdio.h>
#define DEGREE 4
int POLY[DEGREE + 1] = {1, 0, 1, 1}; // CRC Polynomial: x^4 + x + 1

int xor(int a, int b) {
    return a ^ b;
}

void calculateCRC(int data[], int len) {
    for (int i = 0; i <= len - DEGREE - 1; i++) {
        if (data[i] == 1) {
            for (int j = 0; j <= DEGREE; j++)
                data[i + j] = xor(data[i + j], POLY[j]);
        }
    }
}

int main() {
    int data[50], len = 0, totalLen, i;
    char ch;

    // Input: Message
    printf("Enter the data (Message) stream: ");
    while ((ch = getchar()) != '\n')
        data[len++] = ch - '0';

    // Append zeros (for CRC bits)
    for (i = 0; i < DEGREE; i++)
        data[len + i] = 0;

    totalLen = len + DEGREE;

    int temp[50];
    for (i = 0; i < totalLen; i++)
        temp[i] = data[i];

    // Calculate CRC
    calculateCRC(temp, totalLen);

    // Append CRC to original message
    printf("The transmitted frame is: ");
    for (i = 0; i < len; i++)
        printf("%d", data[i]);
    for (i = len; i < totalLen; i++)
        printf("%d", temp[i]);
    printf("\n");

    // Input: Received data
    int recv[50];
    len = 0;
    printf("Enter the stream for which CRC has to be checked: ");
    while ((ch = getchar()) != '\n')
        recv[len++] = ch - '0';

    // Check CRC
    calculateCRC(recv, len);

    int error = 0;
    for (i = len - DEGREE; i < len; i++) {
        if (recv[i] != 0) {
            error = 1;
            break;
        }
    }

    printf("Calculated Checksum: ");
    for (i = len - DEGREE; i < len; i++)
        printf("%d", recv[i]);

    if (error)
        printf("\nError detected in transmission!\n");
    else
        printf("\nNo error detected in transmission.\n");

    return 0;
}