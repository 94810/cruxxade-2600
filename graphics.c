/*      ____________________________________________________                                         
       |_|               == Graphic Code ==               |_|
       |    You can find here all the source code of the    |
       |          graphical part of Cruxxade-2600.          |
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
                                                       \   ,__,
                                                        \  (oo)____
                                                           (__)    )\
                                                              ||--|| *  
*/


#include "graphics.h"

//Even more Vicious Evil Globals Section
extern SDL_Rect cursor[2]; // 0 -> p1 | 1 -> p2
extern SDL_Rect hexaBlue;
extern SDL_Rect hexaGreen;
extern SDL_Rect hexaRed;
extern SDL_Rect p1Token;
extern SDL_Rect p2Token;

void BlitGameboard(T_board board, SDL_Surface* screen, SDL_Surface* sprite){
	SDL_Rect initPos={0,0,0,0}, Pos;
	
	int i, j;

	initPos.x = 0.5*(800-hexaBlue.w);
	initPos.y = 0.5*(600- (board.size)*hexaBlue.h);

	for(i=0;i<board.size;i++){
		for(j=0;j<board.size;j++){
			Pos.x = (4.0/6.0)*hexaBlue.w*(i-j) + initPos.x;
			Pos.y = 0.5*hexaBlue.h*(i+j) + initPos.y;
			SDL_BlitSurface(sprite, &hexaBlue, screen, &Pos);
		}
	}
}
