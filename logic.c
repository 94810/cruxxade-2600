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
void FreeHexaList(Hexa_list **Alive){ //Permet de vider une liste de pions, ils sont stockés via leur adresse.
	while(*Alive != NULL) // Tant que le premier élément de la liste existe,
		SupprEltList(Alive, 0);	//On le vire	
}



void PlaceToken(Param param, T_board *board, Hexa_list **Alive){// permet d'initialiser le plateau en début de partie
	
	int placed=0, i=0, j=0;
	
	board->grid[0][0].val=PLAYER_1; //On place le premier pion du J1
	board->grid[board->size-1][board->size-1].val=PLAYER_1;//Et le second a son opposée
	AppendList(&(Alive[0]), (vect) {0,0}); //On ajoute les pions dans la liste des vivants
	AppendList(&(Alive[0]), (vect) {board->size-1, board->size-1});
	
	board->grid[0][board->size-1].val=PLAYER_2; // On fait de même pour le J2
	board->grid[board->size-1][0].val=PLAYER_2;

	AppendList(&(Alive[1]), (vect) {0, board->size-1});
	AppendList(&(Alive[1]), (vect) {board->size-1, 0});
	
	while(placed<param.closedHex){// Tant qu"il reste une case fermée a placer
		i=rand()%board->size;// on prend 2 valeurs random dans la taille du tableau
		j=rand()%board->size;
		if(board->grid[i][j].val==EMPTY){// si la case correspondante est vide
			board->grid[i][j].val=CLOSED;//On la transforme en case fermée
			placed++; // et une de moins a placer
		}//sinon la boucle refait un tour, pas d'augementation de placed.
	}
	
}

void UpdateScore(int *score, Param param){//MAJ des scores
	FILE *file;

	file=fopen("BestScore.crxx", "a");//Ouverture du fichier en mode ajout

	if(file!=0){//On vérifie que le fichier existe
		fprintf(file, "On a %d board :\n\t%s mark %d\n\t%s mark %d\n", param.boardSize, param.name[0], score[0]+1 , param.name[1], score[1]+1);
	}

	fclose(file);	//Fermeture du fichier
}

void UpdateAlive(T_board board, int player, Hexa_list **Alive, int *playableToken)//MAJ de la liste des pions appartenant a joueur
{
	int i=0;
	Hexa_list *runList=NULL;

	runList = Alive[player];//On crée une copie de la liste des pions du joueur


	while(runList!=NULL){//Tant qu'on a pas exploré toute la liste:
	
		if(board.grid[runList->pos.x][runList->pos.y].val==player){// Est-ce que le pion appartient toujours a ce joueur?, Si oui
			if(IsAlive(runList->pos, board)==FALSE){// Si le pion est mort,
				runList = runList->next;// On passe au pion suivant,
			}
			
			else{
				runList = runList->next;// Sinon, on compte le pion comme "jouable"
				*playableToken=*playableToken+1;// et on passe au pion suivant.
			}
		}
		else{// Si le pion a changé de joueur
			runList = runList->next; //On vire ce pion de la liste des pions de ce joueur
			SupprEltList(Alive+player, i);// et ton passe au pion d'après
			i--;
		}
	
	i++;
	
	}	
}

void AppendList(Hexa_list** init, vect val){// Permet d'ajouter un pion a la fin de la liste
	Hexa_list *list=(*init); //on récupre le debut de la liste.
	

	if(*init==NULL){// si la liste est vide:
		*init = malloc(sizeof(Hexa_list));//On crée une nouvelle liste,
		(*init)->next=NULL;//qui contient un pion,
		(*init)->pos=val;//dont la position est val.
	}
	
	else{//Sinon
		while(list->next!=NULL)//Tant qu'on est pas au bout de la liste...
			list = list->next;//On la parcourt
		
		list->next = malloc(sizeof(Hexa_list));//On ajoute au dernier pion un nouveau pion
		list->next->next=NULL;//qui devient le dernier de la liste
		list->next->pos=val;// et dont la valeur est val
	}
}

void SupprEltList(Hexa_list** init, unsigned int indice){// Permet du supprimer un elt d'une liste
	Hexa_list *list=(*init), *pre=(*init);//On sauvegarde la tête de la liste, deux fois.

	if(list!=NULL){//Si la liste n'est pas vide:
		if(indice>0){//si l'indice est positif
			while(list->next!=NULL && indice>0){//tant qu'on arrive pas a la fin de la liste, et qu'on a pas atteint l'indice voulu
				pre=list;//On avance d'un élément
				list=list->next;//list avance, aussi, mais il est tojours un après pre
				indice --;
			}
			if(pre==list)// Si l'élément est le premier de la liste.
				list=NULL;

			pre->next=list->next;// On bouche le "trou".
			free(list);//On free le pion retiré.
		}
		
		else{
			*init=list->next;//On remplace le début de liste par le second maillon
			free(list);// On libère le 1er maillon.
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
