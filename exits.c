#include "shell.h"

/**
 * copyStringLimited - copies a string up to a certain length
 * @destination: the destination string to be copied to
 * @source: the source string
 * @maxLen: the maximum number of characters to be copied
 * 
 * Returns: The copied string
 */
char *copyStringLimited(char *destination, char *source, int maxLen)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < maxLen - 1)
    {
        destination[i] = source[i];
        i++;
    }

    if (i < maxLen)
    {
        j = i;
        while (j < maxLen)
        {
            destination[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * concatenateStringLimited - concatenates two strings up to a certain length
 * @destination: the first string
 * @source: the second string
 * @maxLen: the maximum number of bytes to be used
 * 
 * Returns: The concatenated string
 */
char *concatenateStringLimited(char *destination, char *source, int maxLen)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;

    while (destination[i] != '\0')
        i++;

    while (source[j] != '\0' && j < maxLen)
    {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < maxLen)
        destination[i] = '\0';

    return result;
}

/**
 * findCharacterInString - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * 
 * Returns: A pointer to the memory area containing the character, or NULL if not found
 */
char *findCharacterInString(char *s, char c)
{
    do {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}
