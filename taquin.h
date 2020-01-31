#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "list.h"

#define MAX_VECTOR 4

typedef struct {
    int len;
    unsigned int valid[MAX_VECTOR];
} move_t;

const move_t moves[MAX_BOARD] = {
    /* 0 */ {2, {1, 3}       },
    /* 1 */ {3, {0, 2, 4}    },
    /* 2 */ {2, {1, 5}       },
    /* 3 */ {3, {0, 4, 6}    },
    /* 4 */ {4, {1, 3, 5, 7} },
    /* 5 */ {3, {2, 4, 8}    },
    /* 6 */ {2, {3, 7}       },
    /* 7 */ {3, {4, 6, 8}    },
    /* 8 */ {2, {5, 7}       }, };

// Initialises game according to the chosen level
Item *initGameTaquin(int level);

// Return 0 if impossible move
int isValidPositionTaquin(Item *grille, int pos);

// Renvoie la solution
void showSolution( Item *goal );

// Renvoie la distance de Manhattan
double getManhattanHeuristic(Item *node);

// Renvoie la profondeur
double getSimpleHeuristics(Item *node);

// renvoie la distance totale entre la piece et l'objectif
int evaluateBoardTaq1(Item *piece);

// Renvoie un enfant de parent valide a pos
Item *getChildNode(Item *parent, int pos);

// Renvoie un enfant de parent, mais fixe f a depth
Item *getChildNodeUCS(Item *parent, int pos);

// Calcule un bfs
void bfs(void);

// Calcule un dfs
void dfs(Item *node);

// Calcule un Astar
void astar(void);

// calcule un UCS
void UCS(void);