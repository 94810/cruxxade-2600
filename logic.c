/*      ____________________________________________________
       |_|               == Logic Code ==                 |_|
       |    You can find here all the source code of the    |
       |          logical part of Cruxxade-2600.            |
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
                                                       \   ,__,
                                                        \  (oo)____
                                                           (__)    )\
                                                              ||--|| *
*/
#include "logic.h"


move ValidMove(vect start, vect end, T_board board){
	vect dpl;
	move Res;
	int normSquare;

	dpl.x=end.x-start.x;
	dpl.y=end.y-start.y;

	if(end.x>=0 && end.x<board.size && end.y>=0 && end.y<board.size && board.grid[end.x][end.y].val==EMPTY && board.grid[end.x][end.y].val!=CLOSED){
		normSquare=(dpl.x*dpl.x)+(dpl.y*dpl.y);

		if(dpl.x*dpl.y>=0){
			if(normSquare>=4 && normSquare<8)
				Res=JUMP;
			else if(normSquare<=2)
				Res=DUPLICATE;
			else
				Res=INVALIDE;
		}

		else{
			if(normSquare==4)
				Res=JUMP;
			else
				Res=INVALIDE;
		}
	}
	else
		Res=INVALIDE;

	return Res;
}


int AllocBoard(T_board* board){
	int i=0;
	int res=0;	
	
	board->grid = (hexa**) malloc(board->size*sizeof(hexa*));
	
	if(board->grid!=NULL){
	
		for(i=0;i<board->size;i++){
			board->grid[i]= (hexa*) malloc(board->size*sizeof(hexa));
			if(board->grid[i]==NULL)
			{
				res=-2;
				i=board->size;
			}
		}
	}
	else
		res=-1;

	return res;						
}

void FreeBoard(T_board* board){
	int i=0;

	for(i=0;i<board->size;i++){
		free(board->grid[i]);	
	}
	
	free(board->grid);
	board->grid=NULL;
}

int InitNewGameboard(int size, T_board* board){	
	int i=0, j=0, k=0;
	
	board->size=size;
	
	AllocBoard(board);	

	for(i=0;i<board->size;i++){
		for(j=0;j<board->size;j++){
			board->grid[i][j].val=EMPTY;
			for(k=0;k<6;k++)
				board->grid[i][j].neighbords[k]=NULL;
		}
	}	
	for(j=0;j<board->size-1;j++){
		for(i=0;i<board->size-1;i++){
			board->grid[i][j].neighbords[DOWN]=&(board->grid[i+1][j+1]);
			board->grid[i][j].neighbords[L_DOWN]=&(board->grid[i][j+1]);
			board->grid[i][j].neighbords[R_DOWN]=&(board->grid[i+1][j]);
		}
		board->grid[i][j].neighbords[L_DOWN]=&(board->grid[i][j+1]);
	}

	for(j=board->size-1;j>0;j--){
		for(i=board->size-1;i>0;i--){
			board->grid[i][j].neighbords[UP]=&(board->grid[i-1][j-1]);
			board->grid[i][j].neighbords[L_UP]=&(board->grid[i-1][j]);
			board->grid[i][j].neighbords[R_UP]=&(board->grid[i][j-1]);
		}
		board->grid[i][j].neighbords[R_UP]=&(board->grid[i][j-1]);
	}
	
	return EXIT_SUCCESS;
}

