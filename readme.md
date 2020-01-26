# IA - Jeux
---
 Travaux pratiques réalisés par Delolme Antonin et Santos Aurélien. L'objectif du projet était de développer trois algorithmes d'intelligence artificielle. DFS , BFS, UCS et ASTAR. Le projet est centré autour de plusieurs packages. Le MAKEFILE va générer 3 exécutables.
 
 ## Lancer les packages
 À la ligne 1 de chaque package, il se situe la ligne `#define MODE 0`. Le mode correspond à l'algorithme utilisé pour résoudre l'exercice.  Voici un tableau des modes disponibles, leur code ainsi que leur accessibilité.
 Algorithme | DFS | BFS | UCS | ASTAR
--- | --- | --- | --- | ---
Commande | `MODE=0` | `MODE=1` | `MODE=2` | `MODE=3` |
Nqueens | OUI | OUI | NON | NON
Knight | NON | OUI | OUI | NON
Nqueens | NON | NON | NON | OUI
 
 ## Nqueens
 Le but du jeu est de résoudre le problème des n reines. Le package nqueens implémente des fonctions de parcours d'arbre. Elles sont très simples, faciles à implémenter mais possèdent des performances médiocres. DFS Parcours en profondeur, (Pour *Depth-First Search*) et BFS Parcours en largeur(Pour *Breadth First Search*) nous donnent rapidement une solution. 
 
 ## Kinght
 Le but du jeu est de résoudre le problème du cavalier. Le paquetage knight dispose d'un BFS modifié, en effet il s'agit d'un UCS. L'algorithme regarde d'abord les état les plus proches dans l'arbre. Le but est de trouver le chemin le plus rapide.
 
 
 ## Taquin
 Le simple algorithme UCS ne pouvait pas suffire pour résoudre un taquin, en effet l'énumération de tous les cas se montre bien trop longue. Nous avons donc implémenté ASTAR, un algorithme basé sur la distance entre l'état courant, et l'objectif. On ne regarde que les cas les plus prometteurs. UCS et BFS n'ont pas été implémentés tellement qu'ils étaient longs pour résoudre un exercice.
 
## Test_list
Ce package sert à débuger nos algorithmes qui agissent sur les listes