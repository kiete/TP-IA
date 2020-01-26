#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "list.h"
#include "taquin.h"
#include "item.h"
#define BOARD_TAQUIN 9

char easy[BOARD_TAQUIN] = {1, 2, 5, 3, 0, 4, 7, 8, 6};
char medium[BOARD_TAQUIN] = { 7, 4, 8, 2, 5, 6, 3, 1, 0 };
char difficult[BOARD_TAQUIN] = { 8, 0, 7, 5, 6, 1, 3, 2, 4 };
char target[BOARD_TAQUIN] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

list_t openList_p;
list_t closedList_p;

int isValidPositionTaquin (Item* grille , int pos){
    char blank = grille->blank ;
    int i;
    for (i = 0; i < moves[blank].len; i++)
    {
        if (pos == moves[blank].valid[i]) return 1;
    }
    return 0;
}

Item *initGameTaquin(int level){
    Item * piece = nodeAlloc();
    switch (level){
    case 1:
        piece->board = easy ;
        piece->blank = 4 ;
        break;
    case 2:
        piece->board = medium;
        piece->blank = 8 ;
        break;
    case 3:
        piece->board = difficult;
        piece->blank = 1 ;
        break;
    default:
        exit(1);
        break;
    }
    
    return piece ;
}

int evaluateBoardTaq1 (Item * piece){
    int i, cpt ;
    cpt = 0;
    for (i=0 ; i<BOARD_TAQUIN ; i++){
        if(piece->board[i] != target[i]) cpt++;
    }
    return cpt;
}

Item* getChildNode(Item *parent, int pos){
    int i;

    if (!isValidPositionTaquin(parent , pos)) return NULL ;

    Item* child = nodeAlloc();
    child->board = malloc(BOARD_TAQUIN);
    child->blank = parent->blank ;
    for (i=0 ; i<BOARD_TAQUIN ; i++){
        child->board[i] = parent->board[i];
    }

    child->board[child->blank] = child->board[pos];
    child->blank = pos;
    child->board[pos] = 0;
    child->depth = parent->depth + 1 ;
    child->parent = parent;
    child->g = getSimpleHeuristics(child);
    child->h = getManhattanHeuristic(child);
    child->f = child->g + child->h ;
    child->size = BOARD_TAQUIN ;

    // printf("Parent:\n");
    // printBoard (parent);
    // printf("child:\n");
    // printBoard(child);
    return child;
}

void astar(void)
{
    
    Item *cur_node, *child_p, *temp;
    int i;
    while (listCount(&openList_p))
    {   /* While items are on the open list */
        /* Get the first item on the open list */
        //printf("%d \n", listCount(&openList_p));
        cur_node = popBest(&openList_p);
        //printBoard(cur_node);
        //printf("%d %d %d\n", listCount(&openList_p), listCount(&closedList_p), evaluateBoardTaq1(cur_node));


        //printBoard(cur_node);

        /* Add it to the "visited" list */
        addLast(&closedList_p, cur_node);
        /* Do we have a solution? */
        if (evaluateBoardTaq1(cur_node) == 0)
        {
            showSolution(cur_node);
            printf("f = %f\n", cur_node->f);
            return;
        }
        else
        {

            /* Enumerate adjacent states */
            for (i = 0; i < MAX_BOARD; i++)
            {
                //printf("OK %d\n" , i);
                child_p = getChildNode(cur_node, i);
                // if (child_p){ 
                //     printf("OK Child cree %d\n", i);
                //     printBoard(child_p);
                // }

                //printf("%f\n" , child_p->f) ;

                if (child_p != NULL)
                { // it's a valid child!
                    /* Ignore this child if already visited */
                    // printf("child_P s=%d\n", child_p->size);
                    // printBoard(child_p);
                    if (!onList(&closedList_p, child_p->board))
                    {
                        temp = onList(&openList_p, child_p->board);
                        if (temp)
                        {
                            //printf("il est la\n");
                            if (temp->f > child_p->f)
                            {
                                delList(&openList_p, temp);
                                addFirst(&openList_p, child_p);
                            }
                        }
                        else
                        {
                            addFirst(&openList_p, child_p);
                            //printf("op = %d\n" , listCount(&openList_p));
                        }
                    }
                    // else //printf("deja vu %d\n" , listCount(&closedList_p));
                    //   if (!onList(&closedList_p, child_p->board)){
                    //     if (onList(&openList_p, child_p->board)){
                    //       if ()
                    //     }
                    //       addLast(&openList_p, child_p);
                    //   }
                }
            }

        //exit(1);

        }
    }

    return;
}

void showSolution( Item *goal )
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal) {
    printBoard( goal );
		goal = goal->parent;
		i++;
  }
  printf("SALUT\n");
  printf("\nLength of the solution = %d\n", i-1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}

double getSimpleHeuristics (Item* node){
    return node->depth;
}
double getManhattanHeuristic (Item* node){
    int i , j , sum;

    j=0;
    sum=0;
    // Pour chaque élément de l'Item
    // printf("1\n");
    for (i=0 ; i < MAX_BOARD ; i++){
        // On trouve son objectif
        while (node->board[i] != target[j]) j++;
        //printf("i=%d target=%d \n", i , node->board[i]);
        sum += abs(i%3 - j%3) + abs(i/3 - j/3);
        j=0;
    }
    return sum;
}

int main (){
    initList(&openList_p);
    initList(&closedList_p);

    printf("\nInitial:");
    Item * plateau = initGameTaquin(3);
    plateau->depth = 0;
    plateau->f = 0 ;
    plateau->size = 9;
    printBoard(plateau);
    printf("\nSearching ...\n");
    addLast(&openList_p, plateau);
    addLast(&closedList_p, plateau);

    astar();

    printf("Finished!\n");

    return 0 ;
}