/*

	
*/

#ifndef LOGIC
#define LOGIC

#include <stdio.h>
#include <stdlib.h>


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

#endif
