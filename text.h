#ifndef TEXT
#define TEXT

#include <SDL/SDL.h>
#include <ctype.h>

int InputCarac(); //If an alphanum carac or return or backspace it Return it else it return -1
SDL_Rect* GetBitmapGlyph(int carac);
void AquireText(SDL_Surface *screen, SDL_Surface *sprite, char *str, int tabsize, SDL_Rect pos);
void PrintText(SDL_Surface *screen, SDL_Surface *sprite, char *str, SDL_Rect pos);

#endif
