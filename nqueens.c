#define MODE 0
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "board.h"

int nb_sol = 0;

list_t openList_p;
list_t closedList_p;

Item* look;


void showSolution( Item *goal )
{
  int i = 0, j;
  //nb_sol++;
  printf("\nSolution:");

  while (goal) {
    printBoard( goal );
		goal = goal->parent;
		i++;
  }
  
  printf("\nLength of the solution = %d\n", i-1);
  printf("nb_sol = %d\n", nb_sol);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}


void bfs( void )
{
  Item *cur_node, *child_p, *temp;
  int i;
  while ( listCount(&openList_p) ) { /* While items are on the open list */
   	
		/* Get the first item on the open list */
    cur_node = popFirst(&openList_p);

		//printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

		/* Add it to the "visited" list */
    addLast(&closedList_p , cur_node);

    /* Do we have a solution? */
    if ( evaluateBoard(cur_node) == 0.0 ) {
      look = cur_node;
      nb_sol++;
      return;

    } else {

      /* Enumerate adjacent states */
      for (i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoard( cur_node, i );
        //printf("%f\n" , child_p->f) ;
   			
        if (child_p != NULL) { // it's a valid child!
          /* Ignore this child if already visited */
          if (!onList(&closedList_p, child_p->board)) addLast(&openList_p, child_p);
        }
      }
    }
  }

  return;
}

void dfs( Item *node ){
	Item *child_p;
	int i;
	if ( evaluateBoard(node) == 0.0 ) {
    look = node;
    nb_sol++;
		return;
	}
	for (i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoard( node, i );
		if (child_p != NULL && !onList(&openList_p, child_p->board)){
			addLast(&closedList_p, child_p);
			dfs(child_p);
		}
	}
}

int main()
{
	// init lists 
  initList(&openList_p);
  initList(&closedList_p);

	
  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard( initial_state );

  printf("\nSearching ...\n");
  
	addLast( &openList_p, initial_state );

  if (MODE == 0){
    dfs(initial_state);
  }else if (MODE == 1){
    bfs();
  }else{
    printf("MODE INVALIDE\n");
    exit(1);
  }
  
  
	printf("Finished!\n");
  showSolution(look);
  // clean lists 
	cleanupList( &openList_p );
  cleanupList( &closedList_p );
	
  return 0;
}
