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


move ValidMove(vect start, vect end, hexa** board, int boardSize){
	vect dpl;
	move Res;
	int normSquare;

	dpl.x=end.x-start.x;
	dpl.y=end.y-start.y;

	if(end.x>=0 && end.x<boardSize && end.y>=0 && end.y<boardSize && board[end.x][end.y].val==EMPTY){
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


int AllocBoard(int boardSize, hexa*** board){
	int i=0;
	int res=0;	
	
	*board = (hexa**) malloc(boardSize*sizeof(hexa*));
	
	if(*board!=NULL){
	
		for(i=0;i<boardSize;i++){
			(*board)[i]= (hexa*) malloc(boardSize*sizeof(hexa));
			if((*board)[i]==NULL)
			{
				res=-2;
				i=boardSize;
			}
		}
	}
	else
		res=-1;

	return res;						
}

void FreeBoard(int boardSize, hexa*** board){
	int i=0;

	for(i=0;i<boardSize;i++){
		free((*board)[i]);	
	}
	
	free(*board);
	*board=NULL;
}

void main()
{	
	hexa** board;
	
	AllocBoard(5, &board);
	FreeBoard(5, &board);
}

