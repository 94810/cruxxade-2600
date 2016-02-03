/*
	Here comme the main program
*/
#include "logic.h"
#include "graphics.h"

//Vicious Evil of The Demonic Demon of Doom Globals Section
const SDL_Rect hexaBlue={0,0,54,54};
const SDL_Rect hexaGreen={56,0,54,54};
const SDL_Rect hexaRed={112,0,54,54};
const SDL_Rect p1Token={0,56,24,34};
const SDL_Rect p2Token={0,92,31,39};

int main(){

	SDL_Surface *screen = NULL, *sprite=NULL, *background=NULL;
	SDL_Event event;
	SDL_Rect pos={0,0,0,0};

	vect tmp;

	T_board board;

	InitNewGameboard(11, &board);

	int exit=1;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 
	
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

	//SDL_ShowCursor(SDL_DISABLE);

	SDL_WM_SetCaption("<===| Cruxxade - 2600 |====>",NULL);
	
	SDL_Surface *temp = IMG_Load("sprite_sheet.png"); //Sprites Loading 
	sprite = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp); 
	
	temp = IMG_Load("background.png"); //Sprites Loading 
	background = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp);
	SDL_BlitSurface(background, NULL, screen, NULL);
	
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
		}
		
				
		//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		BlitGameboard(board, screen, sprite);
		if(tmp.x>=0 && tmp.x<board.size && tmp.y>=0 && tmp.y<board.size){
			pos.x = (4.0/6.0)*hexaBlue.w*(tmp.x-tmp.y) + GetOrigineHex(board).x;
			pos.y = 0.5*hexaBlue.h*(tmp.x+tmp.y) + GetOrigineHex(board).y;
			
			SDL_BlitSurface(sprite, &hexaRed, screen, &pos);
		}
		SDL_Flip(screen);
	}
		
	FreeBoard(&board);
	SDL_Quit();

	return 0;
}
