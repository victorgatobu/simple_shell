#include "shell.h"

/**
 * getListLength - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t getListLength(const list_t *head)
{
    size_t length = 0;

    while (head)
    {
        head = head->next;
        length++;
    }

    return length;
}

/**
 * listToStrings - returns an array of strings from list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToStrings(list_t *head)
{
    list_t *node = head;
    size_t count = getListLength(head);
    char **strArray;
    char *str;

    if (!head || !count)
        return NULL;

    strArray = malloc(sizeof(char *) * (count + 1));
    if (!strArray)
        return NULL;

    for (size_t i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strArray[j]);
            free(strArray);
            return NULL;
        }

        str = _strcpy(str, node->str);
        strArray[i] = str;
    }

    strArray[count] = NULL;
    return strArray;
}

/**
 * printList - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convertNumber(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * findNodeStartsWith - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @nextChar: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *findNodeStartsWith(list_t *head, char *prefix, char nextChar)
{
    char *p = NULL;

    while (head)
    {
        p = startsWith(head->str, prefix);
        if (p && ((nextChar == -1) || (*p == nextChar)))
            return head;
        head = head->next;
    }

    return NULL;
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }

    return -1;
}
