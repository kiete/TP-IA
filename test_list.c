#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TEST LIST

int main()
{
    Item *item;
    char str[3];

    list_t openList;

    initList(&openList);

    for (int i = 0; i < 10; i++)
    {
        item = nodeAlloc();
        item->f = i;
        sprintf(str, "%2d", i);
        initBoard(item , str);
        addLast(&openList, item);
    }
    for (int i = 20; i < 25; i++)
    {
        item = nodeAlloc();
        item->f = i;
        sprintf(str, "%2d", i);
        initBoard(item, str);
        addFirst(&openList, item);
    }

    printList(openList);
    printf("\n");

    Item *node = popBest(&openList);
    printf("best node = %.2f\n", node->f);
    printList(openList);
    printf("\n");

    strcpy(str, "6");
    node = onList(&openList, str);
    if (node)
        printf("found %s: %.2f!\n", str, node->f);
    printList(openList);
    printf("\n");

    node = popFirst(&openList);
    item = nodeAlloc();
    item->f = 50;
    sprintf(str, "50");
    item->board = strdup(str);
    addLast(&openList, item);

    printList(openList);
    node = popFirst(&openList);
    if (node)
        printf("first: %.2f\n", node->f);
    printList(openList);
    printf("\n");

    node = popLast(&openList);
    if (node)
        printf("last: %.2f\n", node->f);
    printList(openList);
    printf("\n");

    printf("clean\n");
    cleanupList(&openList);
    printList(openList);
    printf("\n");

    return 0;
}
