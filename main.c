/*
	Here comme the main program
*/
#include "logic.h"
#include "graphics.h"

//Vicious Evil of The Demonic Demon of Doom Globals Section
const SDL_Rect cursor[2]={{26,56,9,9}, {26,67,9,9}}; // 0 -> p1 | 1 -> p2
const SDL_Rect hexaBlue={0,0,54,54};
const SDL_Rect hexaGreen={56,0,54,54};
const SDL_Rect hexaRed={112,0,54,54};
const SDL_Rect p1Token={0,56,24,34};
const SDL_Rect p2Token={0,92,31,39};

int main(){

	SDL_Surface *screen = NULL, *sprite=NULL;
	SDL_Event event;
	SDL_Rect cursorCoor = {0,0,0,0} ;

	T_board board;

	InitNewGameboard(11, &board);

	int exit=1;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 
	
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_NOFRAME); 

	SDL_ShowCursor(SDL_DISABLE);
	
	SDL_Surface *temp = IMG_Load("sprite_sheet.png"); //Sprites Loading 
	sprite = SDL_DisplayFormatAlpha(temp); //Convert surface to a faster blitting format
	SDL_FreeSurface(temp); 
	
	while(exit)
	{
		SDL_PollEvent(&event);
		
		switch(event.type){
			case SDL_QUIT :
				exit=0;
			break;
			
			case SDL_MOUSEMOTION:
				cursorCoor.x = event.motion.x;
				cursorCoor.y = event.motion.y;
			break;
			
		}
		
				
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		BlitGameboard(board, screen, sprite);
		SDL_BlitSurface(sprite, &cursor[1], screen, &cursorCoor);
		SDL_Flip(screen);
	}
		
	FreeBoard(&board);
	SDL_Quit();

	return 0;
}
