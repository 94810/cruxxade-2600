/*
	for now just random
*/

#include "IA.h"

vect SelectToken(int score, Hexa_list *Alive, T_board board){
	int select=0, exit=1;

	Hexa_list *runList=Alive;

	while(exit){
	
		select=rand()%score;

		runList=Alive;	

		while(runList!=NULL && select>0){
			runList=runList->next;
			select--;
		}

		if(IsAlive(runList->pos, board));
			exit=0;
	}
	
	
	return runList->pos;
}


vect GenDest(vect token, T_board board){

	int i, j, k, exit=1, h=1;
	
	while(exit){
		h=1;
		k=rand()%4;
		
		switch(k){
			case 0:		
				h=-1;
			case 1:
				i=h*(rand()%3);
				j=h*(rand()%3);
			break;

			case 2:
				h=-1;
			case 3:
				i=h*-(rand()%2);
				j=h*(rand()%2);
			break;
		}
		
		if(ValidMove(token, (vect){token.x+i, token.y+j}, board)!=INVALIDE){
			exit=0;
		}
	}

	return (vect){token.x+i, token.y+j};	
}
