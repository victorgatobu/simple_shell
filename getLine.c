#include "shell.h"

/**
 * bufferChainedCommands - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len variable
 * 
 * Returns: Bytes read
 */
ssize_t bufferChainedCommands(info_t *info, char **buf, size_t *len)
{
    ssize_t bytesRead = 0;
    size_t len_p = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handleCtrlC);
#if USE_GETLINE
        bytesRead = getline(buf, &len_p, stdin);
#else
        bytesRead = customGetline(info, buf, &len_p);
#endif
        if (bytesRead > 0)
        {
            if ((*buf)[bytesRead - 1] == '\n')
            {
                (*buf)[bytesRead - 1] = '\0'; /* Remove trailing newline */
                bytesRead--;
            }
            info->linecount_flag = 1;
            removeComments(*buf);
            buildHistoryList(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) Is this a command chain? */
            {
                *len = bytesRead;
                info->cmd_buf = buf;
            }
        }
    }
    return bytesRead;
}

/**
 * getInput - gets a line without the newline character
 * @info: parameter struct
 * 
 * Returns: Bytes read
 */
ssize_t getInput(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t bytesRead = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytesRead = bufferChainedCommands(info, &buf, &len);

    if (bytesRead == -1) /* EOF */
        return (-1);

    if (len) /* We have commands left in the chain buffer */
    {
        j = i; /* Init new iterator to current buf position */
        p = buf + i; /* Get pointer for return */

        checkChain(info, buf, &j, i, len);

        while (j < len) /* Iterate to semicolon or end */
        {
            if (isChain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* Increment past nulled ';'' */

        if (i >= len) /* Reached end of buffer? */
        {
            i = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back pointer to current command position */
        return (_strlen(p)); /* Return length of current command */
    }

    *buf_p = buf; /* Else not a chain, pass back buffer from customGetline() */
    return (bytesRead); /* Return length of buffer from customGetline() */
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * 
 * Returns: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
    ssize_t bytesRead = 0;

    if (*i)
        return (0);

    bytesRead = read(info->readfd, buf, READ_BUF_SIZE);

    if (bytesRead >= 0)
        *i = bytesRead;

    return bytesRead;
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * 
 * Returns: bytesRead
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytesRead = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length)
        bytesRead = *length;

    if (i == len)
        i = len = 0;

    bytesRead = readBuffer(info, buf, &len);

    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = _realloc(p, bytesRead, bytesRead ? bytesRead + k : k + 1);

    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (bytesRead)
        concatenateStringLimited(new_p, buf + i, k - i);
    else
        copyStringLimited(new_p, buf + i, k - i + 1);

    bytesRead += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = bytesRead;

    *ptr = p;
    return bytesRead;
}

/**
 * handleCtrlC - blocks Ctrl-C
 * @sigNum: the signal number
 * 
 * Returns: void
 */
void handleCtrlC(__attribute__((unused))int sigNum)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
