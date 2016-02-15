#ifndef IA
#define IA
#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

vect SelectToken(int score, Hexa_list *Alive, T_board board);
vect GenDest(vect token, T_board board);
int CalcMoveVal(vect start, vect end, move mvt, T_board board);
vect CalcTokenVal(vect token, T_board board, int *score);

void GiveClick(vect *firstClick, vect *secondClick, Hexa_list *Alive, T_board board);
#endif
