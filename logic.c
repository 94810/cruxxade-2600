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
void FreeHexaList(Hexa_list **Alive){
	while(*Alive != NULL)
		SupprEltList(Alive, 0);		
}



void PlaceToken(Param param, T_board *board, Hexa_list **Alive){
	
	int placed=0, i=0, j=0;
	
	board->grid[0][0].val=PLAYER_1;
	board->grid[board->size-1][board->size-1].val=PLAYER_1;
	AppendList(&(Alive[0]), (vect) {0,0});
	AppendList(&(Alive[0]), (vect) {board->size-1, board->size-1});
	
	board->grid[0][board->size-1].val=PLAYER_2;
	board->grid[board->size-1][0].val=PLAYER_2;

	AppendList(&(Alive[1]), (vect) {0, board->size-1});
	AppendList(&(Alive[1]), (vect) {board->size-1, 0});
	
	while(placed<param.closedHex){
		i=rand()%board->size;
		j=rand()%board->size;
		if(board->grid[i][j].val==EMPTY){
			board->grid[i][j].val=CLOSED;
			placed++;
		}
	}
	
}

void UpdateScore(int *score, Param param){
	FILE *file;

	file=fopen("BestScore.crxx", "a");

	if(file!=0){
		fprintf(file, "On a %d board :\n\t%s mark %d\n\t%s mark %d\n", param.boardSize, param.name[0], score[0]+1 , param.name[1], score[1]+1);
	}

	fclose(file);	
}

void UpdateAlive(T_board board, int player, Hexa_list **Alive, int *playableToken)
{
	int i=0;
	Hexa_list *runList=NULL;

	runList = Alive[player];


	while(runList!=NULL){
	
		if(board.grid[runList->pos.x][runList->pos.y].val==player){
			if(IsAlive(runList->pos, board)==FALSE){
				runList = runList->next;
			}
			
			else{
				runList = runList->next;
				*playableToken=*playableToken+1;
			}
		}
		else{
			runList = runList->next;
			SupprEltList(Alive+player, i);
			i--;
		}
	
	i++;
	
	}	
}

void AppendList(Hexa_list** init, vect val){
	Hexa_list *list=(*init);


	if(*init==NULL){	
		*init = malloc(sizeof(Hexa_list));
		(*init)->next=NULL;
		(*init)->pos=val;
	}
	
	else{
		while(list->next!=NULL)
			list = list->next;

		list->next = malloc(sizeof(Hexa_list));
		list->next->next=NULL;
		list->next->pos=val;	
	}
}

void SupprEltList(Hexa_list** init, unsigned int indice){
	Hexa_list *list=(*init), *pre=(*init);

	if(list!=NULL){
		if(indice>0){
			while(list->next!=NULL && indice>0){
				pre=list;
				list=list->next;
				indice --;
			}
			if(pre==list)
				list=NULL;

			pre->next=list->next;
			free(list);
		}
		
		else{
			*init=list->next;
			free(list);
		}
	}

}

move ValidMove(vect start, vect end, T_board board){
	vect dpl;
	move Res;
	int normSquare;

	dpl.x=end.x-start.x;
	dpl.y=end.y-start.y;

	if(end.x>=0 && end.x<board.size && end.y>=0 && end.y<board.size && board.grid[end.x][end.y].val==EMPTY){
		normSquare=(dpl.x*dpl.x)+(dpl.y*dpl.y);

		if(dpl.x*dpl.y>=0){
			if(normSquare>=4 && normSquare<=8)
				Res=JUMP;
			else if(normSquare<=2)
				Res=DUPLICATE;
			else
				Res=INVALIDE;
		}

		else{
			if(normSquare==2)
				Res=JUMP;
			else
				Res=INVALIDE;
		}
	}
	else
		Res=INVALIDE;

	return Res;
}

void playMove(T_board* board, move mvt, Hexa_list **alivePlAct, vect start, vect end, int player, int *score){
	int i=0;

	if(mvt==DUPLICATE){
		board->grid[end.x][end.y].val = player;
		AppendList(alivePlAct, end);
		score[player]+=1;
	}

	else if(mvt==JUMP){
		board->grid[end.x][end.y].val = player;	
		board->grid[start.x][start.y].val = EMPTY;
		AppendList(alivePlAct, end);	
	}

	if(mvt==JUMP || mvt==DUPLICATE){
		for(i=0; i<6 ; i++){
			if(board->grid[end.x][end.y].neighbords[i]!=NULL){
				if(board->grid[end.x][end.y].neighbords[i]->val!=player && (board->grid[end.x][end.y].neighbords[i]->val==PLAYER_2 || board->grid[end.x][end.y].neighbords[i]->val==PLAYER_1) ){
					board->grid[end.x][end.y].neighbords[i]->val=player;
				        switch(i){
						case UP:
							AppendList(alivePlAct, (vect){end.x-1, end.y-1});
						break;
						case DOWN:	
							AppendList(alivePlAct, (vect){end.x+1, end.y+1});	
						break;
						case R_DOWN:	
							AppendList(alivePlAct, (vect){end.x+1, end.y});
						break;
						case L_DOWN:	
							AppendList(alivePlAct, (vect){end.x, end.y+1});
						break;
						case L_UP:	
							AppendList(alivePlAct, (vect){end.x-1, end.y});
						break;
						case R_UP:	
							AppendList(alivePlAct, (vect){end.x, end.y-1});
						break;
					}	
					
					score[player]+=1;
					score[(player+1)%2]-=1;
				}
			
			}
		}
	

	}
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

	j=board->size-1;
	for(i=0;i<board->size-1;i++){
		board->grid[i][j].neighbords[R_DOWN]=&(board->grid[i+1][j]);
	}

	for(j=board->size-1;j>0;j--){
		for(i=board->size-1;i>0;i--){
			board->grid[i][j].neighbords[UP]=&(board->grid[i-1][j-1]);
			board->grid[i][j].neighbords[L_UP]=&(board->grid[i-1][j]);
			board->grid[i][j].neighbords[R_UP]=&(board->grid[i][j-1]);
		}
		board->grid[i][j].neighbords[R_UP]=&(board->grid[i][j-1]);
	}

	j=0;
	for(i=board->size-1;i>0;i--){
		board->grid[i][j].neighbords[L_UP]=&(board->grid[i-1][j]);
	}
	
	return EXIT_SUCCESS;
}

int IsAlive(vect pos, T_board board){
	int res = FALSE, i=0, j=0;
	
	for(i=pos.x-2 ; i<=pos.x ; i++){
		for(j=pos.y-2 ; j<=pos.y ; j++){
			if(j>=0 && i>=0 && j<board.size && i<board.size){
				if(board.grid[i][j].val==EMPTY){
					res = TRUE;
				}
			}
		}
	}

	for(i=pos.x ; i<=pos.x+2 ; i++){
		for(j=pos.y ; j<=pos.y+2 ; j++){
			if(j>=0 && i>=0 && j<board.size && i<board.size){
				if(board.grid[i][j].val==EMPTY){
					res = TRUE;
				}
			}
		}
	}

	i=pos.x+1;
	j=pos.y-1;
	if(j>=0 && i>=0 && j<board.size && i<board.size){
		if(board.grid[i][j].val==EMPTY){
				res = TRUE;
		}
	}	

	i=pos.x-1;
	j=pos.y+1;
	if(j>=0 && i>=0 && j<board.size && i<board.size){
		if(board.grid[i][j].val==EMPTY){
				res = TRUE;
		}
	}	
	return res;
}
