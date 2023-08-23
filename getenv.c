#include "shell.h"

/**
 * retrieveEnvironment - returns the copy of environment variables as a string array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Pointer to an array of strings representing environment variables
 */
char **retrieveEnvironment(info_t *info)
{
    if (!info->environ || info->envChanged)
    {
        info->environ = listToStrings(info->env);
        info->envChanged = 0;
    }

    return (info->environ);
}

/**
 * removeEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 if the variable was deleted, 0 otherwise
 */
int removeEnvironmentVariable(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->envChanged;
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: 0 on success, 1 on failure
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 1;

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->envChanged = 1;
            return 0;
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->envChanged = 1;
    return 0;
}
