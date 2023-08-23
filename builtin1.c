#include "shell.h"

/**
 * displayHistory - displays the history list with line numbers
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int displayHistory(info_t *info)
{
    printListWithLineNumbers(info->history);
    return 0;
}

/**
 * unsetAlias - unsets an alias
 * @info: parameter struct
 * @aliasString: the alias string
 *
 * Returns: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *aliasString)
{
    char *equalSign, originalChar;
    int ret;

    equalSign = _strchr(aliasString, '=');
    if (!equalSign)
        return 1;

    originalChar = *equalSign;
    *equalSign = '\0';
    ret = deleteNodeAtIndex(&(info->alias), getNodeIndex(info->alias, nodeStartsWith(info->alias, aliasString, -1)));
    *equalSign = originalChar;

    return ret;
}

/**
 * setAlias - sets an alias
 * @info: parameter struct
 * @aliasString: the alias string
 *
 * Returns: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *aliasString)
{
    char *equalSign, *aliasValue;

    equalSign = _strchr(aliasString, '=');
    if (!equalSign)
        return 1;

    aliasValue = equalSign + 1;

    if (!*aliasValue)
        return unsetAlias(info, aliasString);

    unsetAlias(info, aliasString);
    return (addNodeEnd(&(info->alias), aliasString, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 *
 * Returns: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
    char *equalSign, *aliasValue;

    if (node)
    {
        equalSign = _strchr(node->str, '=');
        aliasValue = equalSign + 1;

        for (char *a = node->str; a <= equalSign; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(aliasValue);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * manageAlias - manages the alias command
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int manageAlias(info_t *info)
{
    int i = 0;
    char *equalSign, *aliasValue;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equalSign = _strchr(info->argv[i], '=');
        if (equalSign)
            setAlias(info, info->argv[i]);
        else
            printAlias(nodeStartsWith(info->alias, info->argv[i], '='));

        aliasValue = equalSign + 1;
        (void)aliasValue;
    }

    return 0;
}
