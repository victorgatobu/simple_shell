#include "shell.h"

/**
 * safeAtoi - converts a string to an integer with error handling
 * @s: the string to be converted
 * 
 * Returns: Converted number on success, -1 on error
 */
int safeAtoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
        {
            return -1;
        }
    }

    return (int)result;
}

/**
 * printErrorInfo - prints an error message with info details
 * @info: the parameter and return info struct
 * @errorString: string containing specified error type
 * 
 * Returns: Nothing
 */
void printErrorInfo(info_t *info, char *errorString)
{
    _eputs(info->fname);
    _eputs(": ");
    printDecimal(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(errorString);
}

/**
 * printDecimal - prints a decimal (integer) number (base 10)
 * @input: the input number
 * @fd: the file descriptor to write to
 * 
 * Returns: Number of characters printed
 */
int printDecimal(int input, int fd)
{
    int (*printCharFunction)(char) = _putchar;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO)
        printCharFunction = _eputchar;

    if (input < 0)
    {
        absoluteValue = -input;
        printCharFunction('-');
        count++;
    }
    else
    {
        absoluteValue = input;
    }

    current = absoluteValue;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            printCharFunction('0' + current / i);
            count++;
        }
        current %= i;
    }

    printCharFunction('0' + current);
    count++;

    return count;
}

/**
 * convertNumberToString - converts a number to a string
 * @num: number to be converted
 * @base: base of conversion
 * @flags: argument flags
 * 
 * Returns: The converted string
 */
char *convertNumberToString(long int num, int base, int flags)
{
    static char *hexArray;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    hexArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = hexArray[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * removeComments - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 * 
 * Returns: Nothing
 */
void removeComments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
