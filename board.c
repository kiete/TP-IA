#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"


// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;
  
  char* initial = (char*)malloc(MAX_BOARD*sizeof(char));
	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;

  node = nodeAlloc();
	initBoard(node, initial);
  
  node->depth = 0;

  return node;
}

// print a board
void printBoard( Item *node )
{
  assert(node);
	printf("\n");
	for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < MAX_BOARD ; i++) {
    if (i%WH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
		}
  }
	printf("\n");
}


// initialize node's state from a given board
void initBoard(Item *node, char *board) {
  int i;
	assert( node );
	
	node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));

  for (i=0 ; i < MAX_BOARD ; i++){
    node->board[i] = board[i] ;
  }
  return ;
}


// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
  int nb = NB_QUEENS ;
  int i = 0 ;

  for (i = 0; i < MAX_BOARD; i++)
  {
    if (node->board[i] == 1) nb-- ;
  }

  return nb;
}

double evaluateBoardKnight(Item *node) {
  return (double)node->board[MAX_BOARD-1] ;
}


// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition( Item *node, int pos )
{
  int tmpi , tmpj , tmp;
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

  for (int i=0; i<WH_BOARD; i++) {
  	for (int j=0; j<WH_BOARD; j++) {
      if ((node->board[i * WH_BOARD + j] == 1) && ((i == ii) || (j == jj) || (abs(ii - i) == abs(jj - j)))) return 0;
    }
  }
  return 1;
}

// Return 1 si the knight can move to pos, 0 else.
int isValidPositionKnight( Item *node, int pos )
{
  int tmpi , tmpj , tmp;
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

  for (int i=0; i<WH_BOARD; i++) {
  	for (int j=0; j<WH_BOARD; j++) {
      if (node->board[i * WH_BOARD + j] == 1){
        if(abs(ii-i)*abs(jj-j)==2) return 1;
        else return 0;
      } 
    }
  }
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL ;
  int i ;
  
	if ( isValidPosition(node, pos) ) {
    /* allocate and init child node */
    child_p =  nodeAlloc();
    initBoard(child_p , node->board) ;

    /* Make move */
    child_p->board[pos] = 1;

    /* link child to parent for backtrack */
    child_p -> parent = node ;
    child_p -> depth ++ ;
  }

  return child_p;
}

// Return a new item where a new knight is moved at position pos if possible. NULL if not valid
Item *getChildBoardKnight( Item *node, int pos )
{
  Item *child_p = NULL ;
  int i ;
  
	if ( isValidPositionKnight(node, pos)) {
    /* allocate and init child node */
    child_p =  nodeAlloc();
    initBoard(child_p, node->board) ;

    /* Make move */
    for(i = 0 ; i<MAX_BOARD ; i++) child_p->board[i] = 0 ;
    child_p->board[pos] = 1;

    // Set cost
    child_p->f = node->f + 1 ;

    /* link child to parent for backtrack */
    child_p -> parent = node ;
    child_p -> depth ++ ;
  }

  return child_p;
}
