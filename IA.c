/*
	Not only random
*/

#include "IA.h"
void GiveClick(vect *firstClick, vect *secondClick, Hexa_list *Alive, T_board board){
	Hexa_list *runList=Alive;
	int max=0, tmp=0;
	vect vTmp;

	while(runList!=NULL){
		vTmp=CalcTokenVal(runList->pos, board, &tmp);
		if(tmp>=max){
			*firstClick=runList->pos;
			*secondClick=vTmp;
			max=tmp;
		}
		runList=runList->next;
	}
}

int CalcMoveVal(vect start, vect end, move mvt, T_board board){
	int player=board.grid[start.x][start.y].val;
		
	int res=0, i;
	
	if(mvt==DUPLICATE)
		res++;

	for(i=0;i<6;i++){
		if(board.grid[end.x][end.y].neighbords[i]!=NULL){
			if(board.grid[end.x][end.y].neighbords[i]->val!=player && (board.grid[end.x][end.y].neighbords[i]->val==PLAYER_2 || board.grid[end.x][end.y].neighbords[i]->val==PLAYER_1) ){
				res++;
			}
		}
	}

	return res;
}

vect CalcTokenVal(vect token, T_board board, int *score){
	int max=0, tmp=0, i, j;
	vect good;
	move mvt;

	for(i=token.x-2 ; i<=token.x ; i++){
		for(j=token.y-2 ; j<=token.y ; j++){
			if(j>=0 && i>=0 && j<board.size && i<board.size){
				if(board.grid[i][j].val==EMPTY){
					if((i-token.x)*(j-token.y)<=2)
						mvt=DUPLICATE;
					else
						mvt=JUMP;	
					tmp = CalcMoveVal(token, (vect){i,j}, mvt, board);
					if(max <= tmp){
						max=tmp;
						good=(vect){i,j};
					}
				}
			}
		}
	}

	for(i=token.x ; i<=token.x+2 ; i++){
		for(j=token.y ; j<token.y+2 ; j++){
			if(j>=0 && i>=0 && j<board.size && i<board.size){
				if(board.grid[i][j].val==EMPTY){
					if((i-token.x)*(j-token.y)<=2)
						mvt=DUPLICATE;
					else
						mvt=JUMP;	
					tmp = CalcMoveVal(token, (vect){i,j}, mvt, board);
					if(max <= tmp){
						max=tmp;
						good=(vect){i,j};
					}
				}
			}
		}
	}

	i=token.x+1;
	j=token.y-1;
	if(j>=0 && i>=0 && j<board.size && i<board.size){
		if(board.grid[i][j].val==EMPTY){
			mvt=JUMP;	
			tmp = CalcMoveVal(token, (vect){i,j}, mvt, board);
			if(max <= tmp){
				max=tmp;
				good=(vect){i,j};
			}
		}
	}	

	i=token.x-1;
	j=token.y+1;
	if(j>=0 && i>=0 && j<board.size && i<board.size){
		if(board.grid[i][j].val==EMPTY){
			mvt=JUMP;	
			tmp = CalcMoveVal(token, (vect){i,j}, mvt, board);
			if(max <= tmp){
				max=tmp;
				good=(vect){i,j};
			}
		}
	}	
	
	
	*score=max;
	return good;
}

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
