#include "shell.h"

/**
 * checkInteractiveMode - checks if the shell is in interactive mode
 * @info: information struct
 *
 * Returns: 1 if in interactive mode, 0 otherwise
 */
int checkInteractiveMode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: the delimiter string
 * 
 * Returns: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiters)
{
    while (*delimiters)
    {
        if (*delimiters++ == c)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * isAlphabetic - checks if a character is alphabetic
 * @c: the character to check
 * 
 * Returns: 1 if c is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * customAtoi - converts a string to an integer
 * @str: the string to be converted
 * 
 * Returns: 0 if no numbers in string, converted number otherwise
 */
int customAtoi(char *str)
{
    int index, sign = 1, foundDigits = 0, result = 0;
    unsigned int num = 0;

    for (index = 0; str[index] != '\0' && foundDigits != 2; index++)
    {
        if (str[index] == '-')
        {
            sign *= -1;
        }
        if (str[index] >= '0' && str[index] <= '9')
        {
            foundDigits = 1;
            num *= 10;
            num += (str[index] - '0');
        }
        else if (foundDigits == 1)
        {
            foundDigits = 2;
        }
    }

    if (sign == -1)
    {
        result = -num;
    }
    else
    {
        result = num;
    }

    return result;
}
