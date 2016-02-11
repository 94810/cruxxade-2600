#include "text.h"
#include "police.h"
#include <stdio.h>

int InputCarac(){
	int res=-1;
	SDL_Event event;

	SDL_WaitEvent(&event);

	if(event.type==SDL_KEYDOWN && ( isalpha(event.key.keysym.sym) || event.key.keysym.sym=='\r' || event.key.keysym.sym=='\b' || event.key.keysym.sym==' ') ){
		res=event.key.keysym.sym;
	}
	return res;
}

SDL_Rect* GetBitmapGlyph(int carac){
	int i=0;
	
	if(isalpha(carac))
		i=carac-'a';
	
	else if(isdigit(carac))
		i=carac-'0'+26;

	else if(carac==' ')
		i=38;

	return &(police[i]);
}

void AquireText(SDL_Surface *screen, SDL_Surface *sprite, char *str, int tabsize, SDL_Rect pos){
	int i=0, carac=-1, exit=1;
	SDL_Rect posAct=pos;

	str[0]='\0';
		
	while(exit){

		carac=InputCarac();		
		posAct.x=pos.x+(police[1].w*i);
		
		if(carac!=-1){
			if(carac=='\b'){
				if(i>0){
					posAct.x=posAct.x-police[1].w; //On efface
					str[i-1]='\0';
				}	
				SDL_BlitSurface(sprite, &(police[36]), screen, &posAct);
				if(i>0)
					i--; //On ramene le curseur
			}
			
			else if(carac=='\r'){
				exit=0;  //On valide la chaine
			}

			else if(i<tabsize-1){
				SDL_BlitSurface(sprite, GetBitmapGlyph(carac), screen, &posAct);
				str[i]= (char) carac;
				str[i+1]='\0';
				if(i<tabsize-2)
					i++;
			}
		}
		
		SDL_Flip(screen);
	}
}

void PrintText(SDL_Surface *screen, SDL_Surface *sprite, char *str, SDL_Rect pos){
	int carac = (int) str[0], i=0;
	SDL_Rect posAct = pos; 	

	for(i=1 ; carac!='\0' ; i++){
		SDL_BlitSurface(sprite, GetBitmapGlyph(carac), screen, &posAct);
		posAct.x = posAct.x + police[0].w;
		carac = (int) str[i];
	}
}
