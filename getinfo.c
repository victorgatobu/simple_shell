#include "shell.h"

/**
 * initializeInfo - initializes the info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * populateInfo - populates the info_t struct with relevant data
 * @info: struct address
 * @args: argument vector
 */
void populateInfo(info_t *info, char **args)
{
    int i = 0;

    info->fname = args[0];
    if (info->arg)
    {
        info->argv = stringToArray(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = duplicateString(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replaceAlias(info);
        replaceVariables(info);
    }
}

/**
 * releaseInfo - releases the memory used by fields in the info_t struct
 * @info: struct address
 * @freeAll: true if freeing all fields
 */
void releaseInfo(info_t *info, int freeAll)
{
    freeArray(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (freeAll)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            freeList(&(info->env));
        if (info->history)
            freeList(&(info->history));
        if (info->alias)
            freeList(&(info->alias));
        freeArray(info->environ);
        info->environ = NULL;
        free(info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        flushBuffer();
    }
}
