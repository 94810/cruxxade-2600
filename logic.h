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

#define UP 0
#define DOWN 1
#define R_UP 2
#define L_DOWN 3
#define R_DOWN 4
#define L_UP 5

//Début Structure de Donnée

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

typedef struct {
	int size;
	hexa** grid;	
} T_board;
//Fin Strucutre de Donnée 

//Début Prototype
move ValidMove(vect start, vect end, T_board board);
int AllocBoard(T_board* board); //return 0 if sucess ; Neg value otherwise
void FreeBoard(T_board* board);
int InitNewGameboard(int size, T_board* board);
//Fin Prototype
#endif
