/*      ____________________________________________________
       |_|              == Graphics Header ==             |_|
       |  You can find here all data struture and function  |
       |  prototype of the graphical part of Cruxxade-2600. |
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
						       \   ,__,
						        \  (oo)____
           						   (__)    )\
              					              ||--|| *
*/


#ifndef GRAPHIX
#define GRAPHIX

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "logic.h"
#include <math.h>

vect GetOrigineHex(T_board board);
void BlitGameboard(T_board board, SDL_Surface* screen, SDL_Surface* sprite);
vect GetHexaCoor(T_board board, vect cursor);
#endif
