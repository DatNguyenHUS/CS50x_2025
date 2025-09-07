#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define U8  char
#define U16 unsigned short
#define U32 unsigned int
#define U64 unsigned long long  //0 to 18,446,744,073,709,551,615
#define L64 long long           //-(2^63) to (2^63)-1

#define VALID_CREDIT_NUMBER   1
#define INVALID_CREDIT_NUMBER 0

U8  chk_format(U8 * buff)
{
    while (*buff != '\0')
    {
        if (*buff > 47 && *buff < 58)
        {
            buff  = buff + sizeof(U8);
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

U8  chk_length(U8 * buff)
{
    return strlen(buff);
}

U8  chk_luhn_algo(U8 * buff)
{
    U8 sum = 0;
    U8 isOdd = 1; // rightmost digit is odd position
    U8 cnt = strlen(buff);
    buff = buff + (strlen(buff) - 1) * sizeof(U8); // point to the last digit
    while (cnt > 0)
    {
        U8 digit = *buff - '0';
        if (isOdd)
        {
            sum += digit;
        }
        else
        {
            U8 doubled = digit * 2;
            if (doubled > 9)
            {
                sum += doubled / 10;    // add the first digit
                // OR sum += 1; // same as adding the first digits of doubled because max doubled can be 18
                sum += doubled % 10;    // add the second digit
            }
            else
            {
                sum += doubled;
            }
        }
        isOdd = !isOdd;
        buff = buff - sizeof(U8);
        cnt--;
    }
    return (sum % 10 == 0) ? VALID_CREDIT_NUMBER : INVALID_CREDIT_NUMBER;
}

U8  check_valid_credit_number(U8 * buff)
{
    U8  number_len = chk_length(buff);
    if (chk_format(buff))
    {
        if (number_len == 13 ||
            number_len == 15 ||
            number_len == 16)
        {
            if (chk_luhn_algo(buff) )
            {
                return VALID_CREDIT_NUMBER;
            }
        }
    }
    return INVALID_CREDIT_NUMBER;
}

int main(void)
{
    L64 number;
    U8  buff[100];
    printf("Enter a number: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strlen(buff) - 1] = '\0';
    if (check_valid_credit_number(buff) == VALID_CREDIT_NUMBER)
    {
        if (strlen(buff) == 15 && (buff[0] == '3' && (buff[1] == '4' || buff[1] == '7')))
        {
            printf("AMEX\n");
        }
        else if (strlen(buff) == 16 && (buff[0] == '5') && (buff[1] >= '1' && buff[1] <= '5'))
        {
            printf("MASTERCARD\n");
        }
        else if ((strlen(buff) == 13 || strlen(buff) == 16) && buff[0] == '4')
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
