#include "shell.h"

/**
 * displayEnvironment - prints the current environment variables
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int displayEnvironment(info_t *info)
{
    printListStr(info->env);
    return 0;
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: env variable name
 *
 * Returns: the value of the variable or NULL if not found
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = startsWith(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * setEnvironmentVariable - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int setEnvironmentVariable(info_t *info)
{
    if (info->argc != 3)
    {
        eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int unsetEnvironmentVariable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        eputs("Too few arguments.\n");
        return 1;
    }

    for (i = 1; info->argv[i]; i++)
        _unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * initializeEnvironmentList - populates environment linked list
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int initializeEnvironmentList(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    info->env = node;
    return 0;
}
