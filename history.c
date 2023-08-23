#include "shell.h"

/**
 * obtainHistoryFile - gets the path to the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file path
 */
char *obtainHistoryFile(info_t *info)
{
    char *buf, *homeDir;

    homeDir = _getenv(info, "HOME=");
    if (!homeDir)
        return (NULL);

    buf = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);

    buf[0] = '\0';
    _strcpy(buf, homeDir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return buf;
}

/**
 * writeHistoryToFile - writes history to a file
 * @info: parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int writeHistoryToFile(info_t *info)
{
    ssize_t fd;
    char *filename = obtainHistoryFile(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * readHistoryFromFile - reads history from a file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 on failure
 */
int readHistoryFromFile(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fileSize = 0;
    struct stat st;
    char *buf = NULL, *filename = obtainHistoryFile(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fileSize = st.st_size;

    if (fileSize < 2)
        return (0);

    buf = malloc(sizeof(char) * (fileSize + 1));
    if (!buf)
        return (0);

    rdlen = read(fd, buf, fileSize);
    buf[fileSize] = '\0';

    if (rdlen <= 0)
        return (free(buf), 0);

    close(fd);

    for (i = 0; i < fileSize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return info->histcount;
}

/**
 * buildHistoryList - adds an entry to the history linked list
 * @info: parameter struct
 * @buf: buffer
 * @linecount: history line count
 *
 * Return: 0 on success
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: parameter struct
 *
 * Return: new histcount
 */
int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}
