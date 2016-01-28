/*
	Here comme the main program
*/
#include "logic.h"
#include "graphics.h"

int main(){

	SDL_Surface *screen = NULL, *sprite=NULL;
	SDL_Event event;
	SDL_Rect cursor = {26,56,9,9};
	SDL_Rect cursorCoor = {0,0,0,0} ;

	int exit=1;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 
	
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE); 

	SDL_ShowCursor(SDL_DISABLE);
	
	SDL_Surface *temp = IMG_Load("sprite_sheet.png"); //Sprites Loading 
	sprite = SDL_DisplayFormat(temp); //Convert surface to a faster blitting format
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
		SDL_BlitSurface(sprite, &cursor, screen, &cursorCoor);
		SDL_Flip(screen);
	}
		
	SDL_Quit();

	return 0;
}
