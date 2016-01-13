/*      ____________________________________________________
       |_|              == Logic Header ==                |_|
       |  You can find here all data struture and function  |
       |   prototype of the logical part of Cruxxade-2600.  |
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
						       \   ,__,
						        \  (oo)____
           						   (__)    )\
              					              ||--|| *
*/

#ifndef LOGIC
#define LOGIC

#include <stdio.h>
#include <stdlib.h>


//Début Structure de Donnée

typedef enum{
	UP, DOWN, R_UP, L_DOWN, R_DOWN, L_UP
} neighbord;

typedef enum{
	JUMP, DUPLICATE, INVALIDE
} move;

typedef enum{
	EMPTY, PLAYER_1, PLAYER_2, CLOSED
} case_value;

typedef struct{
	int x;
	int y;
} vect;

typedef struct hexa{
	case_value val;
	struct hexa* neighbords[6];
} hexa;

//Fin Strucutre de Donnée 

//Début Prototype
move ValidMove(vect start, vect end, hexa** board, int boardSize);
int AllocBoard(int boardSize, hexa*** board); //return 0 if sucess ; Neg value otherwise
void FreeBoard(int boardSize, hexa*** board);
//Fin Prototype
#endif
