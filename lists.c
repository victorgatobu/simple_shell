#include "shell.h"

/**
 * addNodeToStart - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to new head node
 */
list_t *addNodeToStart(list_t **head, const char *str, int num)
{
    list_t *newHead;

    if (!head)
        return NULL;

    newHead = malloc(sizeof(list_t));
    if (!newHead)
        return NULL;

    _memset((void *)newHead, 0, sizeof(list_t));
    newHead->num = num;

    if (str)
    {
        newHead->str = _strdup(str);
        if (!newHead->str)
        {
            free(newHead);
            return NULL;
        }
    }

    newHead->next = *head;
    *head = newHead;

    return newHead;
}

/**
 * addNodeToEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to new node
 */
list_t *addNodeToEnd(list_t **head, const char *str, int num)
{
    list_t *newNode, *node;

    if (!head)
        return NULL;

    node = *head;
    newNode = malloc(sizeof(list_t));
    if (!newNode)
        return NULL;

    _memset((void *)newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = _strdup(str);
        if (!newNode->str)
        {
            free(newNode);
            return NULL;
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return newNode;
}

/**
 * printListStrings - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: number of nodes in the list
 */
size_t printListStrings(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * deleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prevNode;
    unsigned int currentIndex = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;

    while (node)
    {
        if (currentIndex == index)
        {
            prevNode->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        currentIndex++;
        prevNode = node;
        node = node->next;
    }

    return 0;
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of pointer to head node
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
    list_t *node, *nextNode, *head;

    if (!headPtr || !*headPtr)
        return;

    head = *headPtr;
    node = head;

    while (node)
    {
        nextNode = node->next;
        free(node->str);
        free(node);
        node = nextNode;
    }

    *headPtr = NULL;
}
