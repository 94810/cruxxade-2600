/*
	Here comme the main programi
	Use SDL 1.2 and SDL_Image
	A Migration to SDL 2.0 would be great.
*/
#include "logic.h"
#include "graphics.h"

//Vicious Evil of The Demonic Demon of Doom Globals Section

SDL_Rect hexaBlue={0,0,54,54};
SDL_Rect hexaGreen={56,0,54,54};
SDL_Rect hexaRed={112,0,54,54};
SDL_Rect hexaBlack={168,0,54,54};
SDL_Rect Token[2]={{0,56,24,34},{0,92,31,39}};
SDL_Rect winText[3]={{46,112,364,66},{46,56,367,54},{46,180,165,50}};
 
typedef struct {
	int boardSize;
	char name[2][15];
	int gameMode;
}Param;

void NewGame(SDL_Surface *screen, SDL_Surface *sprite, Param param){
	int exit=1, goodClick=0, player=0, i=0, j=0;
	SDL_Event event;
	SDL_Rect pos={0,0,0,0};

	move actMv;

	int score[2]={0};

	Hexa_list* Alive[2]={NULL,NULL};	 
	
	vect tmp, firstClick, secondClick;

	T_board board;

	InitNewGameboard(param.boardSize, &board);
	
	board.grid[0][0].val=PLAYER_1;
        AppendList(Alive,(vect){0,0}); // C99 Compound Literals here


	board.grid[board.size-1][board.size-1].val=PLAYER_2;
	AppendList(Alive+1,(vect){board.size-1, board.size-1}); // Again


	while(exit)
	{
		SDL_PollEvent(&event);
		
		switch(event.type){
			case SDL_QUIT :
				exit=0;
			break;
			
			case SDL_MOUSEMOTION:
				tmp.x = event.motion.x;
				tmp.y = event.motion.y;
				
				tmp = GetHexaCoor(board, tmp);
			break;
	
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button==SDL_BUTTON_LEFT){
					if(goodClick==0){
						tmp = (vect) {event.button.x, event.button.y};
						tmp = GetHexaCoor(board, tmp);
						if(tmp.x>=0 && tmp.x<board.size && tmp.y>=0 && tmp.y<board.size){
							if(player==board.grid[tmp.x][tmp.y].val){
								firstClick = tmp;
								goodClick++;
							}
						}
					}
					
					else if(goodClick==1){
						secondClick = (vect) {event.button.x, event.button.y};
						secondClick = GetHexaCoor(board, secondClick);

						actMv = ValidMove(firstClick, secondClick, board);
		
						if(actMv!=INVALIDE){
							goodClick++;
						}	
						
					}
				}
				
				else if(event.button.button==SDL_BUTTON_RIGHT){
					goodClick = 0;
				}		
			break;
		}

		if(goodClick==2){
			goodClick=0; //Reset click count
			playMove(&board, actMv,&(Alive[player]) ,firstClick, secondClick, player, score); // Play the move
			player=(player+1)%2; // Change player
			UpdateAlive(board, player, Alive); //Update Alive Pawn		
		}
				
		BlitGameboard(board, screen, sprite);
		
		if(tmp.x>=0 && tmp.x<board.size && tmp.y>=0 && tmp.y<board.size){
			pos.x = (4.0/6.0)*hexaBlue.w*(tmp.x-tmp.y) + GetOrigineHex(board.size).x;
			pos.y = 0.5*hexaBlue.h*(tmp.x+tmp.y) + GetOrigineHex(board.size).y;
			
			SDL_BlitSurface(sprite, &hexaRed, screen, &pos);
		}

		SDL_Flip(screen);
		
		if(Alive[player]==NULL){
			player=player+1%2; //Compute final score
			for(i=0;i<board.size;i++){
				for(j=0;j<board.size;j++){
					if(board.grid[i][j].val==EMPTY)
						score[player]+=1;
				}		
			}
			
			BlitWinner(sprite, screen, score);
					
			SDL_Flip(screen);
			
			SDL_Delay(50); //Prevent closing too soon
			
			while(exit){
				SDL_WaitEvent(&event);
				if(event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_QUIT)
					exit=0;
			}
		}
	}

	FreeBoard(&board);
}


int main(){

	Param param={11, {"Granolax","Orangilux"}, 0};
		
	SDL_Surface *screen = NULL, *sprite=NULL, *background=NULL;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 
	
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

	if(screen==NULL)
		abort();

	SDL_WM_SetCaption("<===| Cruxxade - 2600 |====>",NULL);
	
	SDL_Surface *temp = IMG_Load("sprite_sheet.png"); //Sprites Loading 
	sprite = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp); 
	
	temp = IMG_Load("background.png"); //Sprites Loading 
	background = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp);
	SDL_BlitSurface(background, NULL, screen, NULL);

	//THUG ZONE 

	SDL_Event event;
	int i=1;
	char carac;
	
	while(i){
		SDL_WaitEvent(&event);
		
		switch(event.type){
			case SDL_QUIT:
				i=0;			
			break;
			case SDL_KEYDOWN:
				printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));
			break;
		}

	}
	

	//THUG ZONE
	
	NewGame(screen, sprite, param); //start New Game on new board

	EraseBoard(11, screen, sprite);
	
	SDL_Flip(screen);
			
	SDL_Delay(2000);
	SDL_Quit();

	return 0;
}
