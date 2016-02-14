/*
	Here comme the main programi
	Use SDL 1.2 and SDL_Image
	A Migration to SDL 2.0 would be great.
*/
#include "logic.h"
#include "graphics.h"
#include "text.h"
#include "IA.h"
//Vicious Evil of The Demonic Demon of Doom Globals Section

SDL_Rect hexaT[3]={{0,0,54,54},{56,0,54,54},{112,0,54,54}};
SDL_Rect hexaBlack={168,0,54,54};
SDL_Rect Token[2]={{0,56,24,34},{0,92,31,39}};
SDL_Rect winText[3]={{46,112,364,66},{46,56,367,54},{46,180,165,50}};
SDL_Rect arrow={121,232,19,18};
SDL_Rect closed={26,64,19,25};

void NewGame(SDL_Surface *screen, SDL_Surface *sprite, Param param){
	int exit=1, goodClick=0, player=0, i=0, j=0;
	
	int playableToken=2;

	SDL_Event event;
	SDL_Rect pos={0,0,0,0};

	move actMv;

	int score[2]={2,2};

	Hexa_list* Alive[2]={NULL,NULL};	 
	
	vect tmp, pretmp={0,0},firstClick={-1,-1}, secondClick;

	T_board board;

	InitNewGameboard(param.boardSize, &board);
	
	PlaceToken(param, &board, Alive);

	BlitGameboard(board, screen, sprite); //Update the whole board

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
								DrawOneHex(board, screen, sprite, firstClick, 1);	
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
				
				else if(event.button.button==SDL_BUTTON_RIGHT&&goodClick==1){
					DrawOneHex(board, screen, sprite, firstClick, 0);
					firstClick=(vect){-1,-1};	
					goodClick = 0;
				}		
			break;
		}

		if(goodClick==2){
			goodClick=0; //Reset click count
			playMove(&board, actMv,&(Alive[player]) ,firstClick, secondClick, player, score); // Play the move
			player=(player+1)%2; // Change player
			playableToken=0;
			UpdateAlive(board, player, Alive, &playableToken); //Update Alive Pawn
			BlitGameboard(board, screen, sprite); //Update the whole board
			firstClick=(vect){-1,-1};
		}
	
		
		if(tmp.x>=0 && tmp.x<board.size && tmp.y>=0 && tmp.y<board.size){
			if(pretmp.x!=tmp.x || pretmp.y != tmp.y){
				if(pretmp.x != firstClick.x || pretmp.y != firstClick.y)
					DrawOneHex(board, screen, sprite, pretmp, 0);
				if(tmp.x != firstClick.x || tmp.y != firstClick.y)	
					DrawOneHex(board, screen, sprite, tmp, 2);
				pretmp=tmp;
			}
		}

		if(player==PLAYER_1){
			pos = (SDL_Rect) {568, 526, 210, 23};
			SDL_FillRect(screen, &pos, SDL_MapRGB(screen->format, 0, 0, 0));
			pos.x = 21;
		}
		else{
			pos = (SDL_Rect) {21,526, 210, 23};
			SDL_FillRect(screen, &pos, SDL_MapRGB(screen->format, 0, 0, 0));
			pos.x=568;
		}
		
		PrintText(screen , sprite, param.name[player], pos);

		SDL_Flip(screen);
		
		if(param.gameMode==1 && player==PLAYER_2 && playableToken!=0){
			firstClick=SelectToken(score[player], Alive[player], board);
			secondClick=GenDest(firstClick, board);
			goodClick=2;
		}
		if(playableToken==0){
			player=player+1%2; //Compute final score
			for(i=0;i<board.size;i++){
				for(j=0;j<board.size;j++){
					if(board.grid[i][j].val==EMPTY)
						score[player]+=1;
				}		
			}
			
			BlitWinner(sprite, screen, score);
					
			SDL_Flip(screen);
			
			UpdateScore(score, param);			
			
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

Param menu(SDL_Surface *screen, SDL_Surface *sprite){
	int exit=1, menuSelect=0;

	char str[10]={0};
	
	Param param={5, {"Granolax", "Orangilux"}, 0, 0};

	SDL_Event event;

	int arrowPosYbase = 197; 

	SDL_Rect pos, arrowPos={240, arrowPosYbase, arrow.w, arrow.h};

	SDL_BlitSurface(sprite, &arrow, screen, &arrowPos);

	PrintText(screen, sprite,"new game"  ,(SDL_Rect){260,194,0,0});

	PrintText(screen, sprite,"board size" ,(SDL_Rect){260,226,0,0}) ;

	sprintf(str, " %d", param.boardSize);
	PrintText(screen, sprite, str, (SDL_Rect){490,226,0,0});
	
	PrintText(screen, sprite,"closed hex" ,(SDL_Rect){260,256,0,0}) ;

	sprintf(str, " %d", param.closedHex);
	PrintText(screen, sprite, str, (SDL_Rect){490,256,0,0});
		
	PrintText(screen, sprite,"game mode",(SDL_Rect){260,286,0,0});
	
	PrintText(screen, sprite, "pvp", (SDL_Rect){490,286,0,0});
	
	while(exit){
		SDL_WaitEvent(&event);
		if(event.type==SDL_KEYDOWN){
			switch(event.key.keysym.sym){
				
				case SDLK_j:
					SDL_FillRect(screen, &arrowPos, SDL_MapRGB(screen->format, 0, 0, 0));
					menuSelect=(menuSelect+1)%4;
					arrowPos.y = arrowPosYbase+(menuSelect*30);
					SDL_BlitSurface(sprite, &arrow, screen, &arrowPos);
				break;


				case SDLK_RETURN:
					switch(menuSelect){
						case 0:
							exit=0;
							EraseBoard(11, screen, sprite);
						break;
						
						case 1:
							pos=(SDL_Rect){490,226,90,23};
							param.boardSize=(param.boardSize-2)%9+3;
							sprintf(str, " %d", param.boardSize);
							SDL_FillRect(screen, &pos , SDL_MapRGB(screen->format, 0, 0, 0));
							PrintText(screen, sprite, str, (SDL_Rect){490,226,0,0});
							if(param.closedHex>=(param.boardSize*param.boardSize-5)){
								param.closedHex=0;
								pos=(SDL_Rect){490,256,90,23};
								sprintf(str, " %d", param.closedHex);
								SDL_FillRect(screen, &pos , SDL_MapRGB(screen->format, 0, 0, 0));
								PrintText(screen, sprite, str, (SDL_Rect){490,256,0,0});
							}
						break;

						case 2:
							pos=(SDL_Rect){490,256,90,23};
							param.closedHex=(param.closedHex+1)%30;
							if(param.closedHex>=(param.boardSize*param.boardSize-10))
								param.closedHex=0;
							sprintf(str, " %d", param.closedHex);
							SDL_FillRect(screen, &pos , SDL_MapRGB(screen->format, 0, 0, 0));
							PrintText(screen, sprite, str, (SDL_Rect){490,256,0,0});
						break;

						case 3:
							pos=(SDL_Rect){490,286,90,23};
							param.gameMode=(param.gameMode+1)%2;
							SDL_FillRect(screen, &pos , SDL_MapRGB(screen->format, 0, 0, 0));
							if(param.gameMode==0)
								PrintText(screen, sprite, "pvp", (SDL_Rect){490,286,0,0});
							else	
								PrintText(screen, sprite, "pvc", (SDL_Rect){490,286,0,0});
						break;
					}
				break;
				default:
				break;
			}
		}

		SDL_Flip(screen);
	}

	if(param.gameMode==0){
		PrintText(screen, sprite, "player 1" ,(SDL_Rect){250,194,0,0});
		PrintText(screen, sprite,"player 2" ,(SDL_Rect){250,226,0,0});
		AquireText(screen, sprite, param.name[0], 10, (SDL_Rect) {450, 194, 0, 0});
		AquireText(screen, sprite, param.name[1], 10, (SDL_Rect) {450, 226, 0, 0});	

	}

	else{
		PrintText(screen, sprite,"player" ,(SDL_Rect){250,194,0,0});
		AquireText(screen, sprite, param.name[0], 10, (SDL_Rect) {450, 194, 0, 0});
	}

	return param;
}

int main(){

	Param param;
		
	SDL_Surface *screen = NULL, *sprite=NULL, *background=NULL;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 

	time_t t;
	
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

	if(screen==NULL)
		abort();
	
	srand(time(&t));

	SDL_WM_SetCaption("<===| Cruxxade - 2600 |====>",NULL);
	
	SDL_Surface *temp = IMG_Load("sprite_sheet.png"); //Sprites Loading 
	sprite = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp); 
	
	temp = IMG_Load("background.png"); //Sprites Loading 
	background = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp);
	SDL_BlitSurface(background, NULL, screen, NULL);
	
	param=menu(screen, sprite);	

	EraseBoard(11, screen, sprite);
	
	NewGame(screen, sprite, param); //start New Game on new board
	
	SDL_Flip(screen);
			
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	SDL_Quit();

	return 0;
}
