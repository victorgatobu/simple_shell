#include "shell.h"

/**
 * printToStderr - prints a string to stderr
 * @str: the string to be printed
 * 
 * Returns: Nothing
 */
void printToStderr(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        printCharToStderr(str[i]);
        i++;
    }
}

/**
 * printCharToStderr - writes a character to stderr
 * @c: The character to print
 * 
 * Returns: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int printCharToStderr(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * printCharToFD - writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 * 
 * Returns: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int printCharToFD(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * printStringToFD - writes a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * 
 * Returns: the number of characters printed
 */
int printStringToFD(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;

    while (*str)
    {
        i += printCharToFD(*str++, fd);
    }

    return i;
}
