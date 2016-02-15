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
#include <time.h>

#define UP 0
#define DOWN 1
#define R_UP 2
#define L_DOWN 3
#define R_DOWN 4
#define L_UP 5
#define TRUE 1
#define FALSE 0
//Début Structure de Donnée
 
typedef struct {
	int boardSize;
	char name[2][10];
	int gameMode;
	int closedHex;
}Param;

typedef enum{
	JUMP, DUPLICATE, INVALIDE
} move;

typedef enum{
	PLAYER_1=0, PLAYER_2=1, EMPTY,CLOSED
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

typedef struct list{
	vect pos;	
	struct list* next;	
}Hexa_list;


//Fin Strucutre de Donnée 

//Début Prototype
move ValidMove(vect start, vect end, T_board board);
int AllocBoard(T_board* board); //return 0 if sucess ; Neg value otherwise
void FreeBoard(T_board* board);
int InitNewGameboard(int size, T_board* board);
int IsAlive(vect pos, T_board board);
void playMove(T_board* board, move mvt, Hexa_list **alivePlAct, vect start, vect end, int player, int *score);
void AppendList(Hexa_list** init, vect val);
void SupprEltList(Hexa_list** init, unsigned int indice);
void UpdateAlive(T_board board, int player, Hexa_list **Alive, int *playableToken);
void UpdateScore(int *score, Param param);
void PlaceToken(Param param, T_board *board, Hexa_list **Alive);
void FreeHexaList(Hexa_list **Alive);
//Fin Prototype
#endif
