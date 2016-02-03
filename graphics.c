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
extern SDL_Rect hexaBlue;
extern SDL_Rect hexaGreen;
extern SDL_Rect hexaRed;
extern SDL_Rect p1Token;
extern SDL_Rect p2Token;

vect GetOrigineHex(T_board board){
	vect pos;

	pos.x = 0.5*(800-hexaBlue.w);
	pos.y = 0.5*(600-(board.size)*hexaBlue.h);
	
	return pos;
}

void BlitGameboard(T_board board, SDL_Surface* screen, SDL_Surface* sprite){
	SDL_Rect Pos;
	vect initPos = GetOrigineHex(board);
	
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

vect GetHexaCoor(T_board board, vect cursor){
	vect initPos = GetOrigineHex(board), res;	
	
	double x, y, xr, yr, m, p;
	
	int k=0;

	initPos.x=initPos.x+(hexaBlue.w/2);
	initPos.y=initPos.y;
	
	x = (cursor.x-initPos.x) / ((4.0/6.0)*hexaBlue.w);
	y = (cursor.y-initPos.y) / (0.5*hexaBlue.h);
	

	k= (int)floor(x)%2 + (int)floor(y)%2;
	m = 4.0/2.0;
	p = 2.0/3.0;

	xr = x - floor(x);
	yr = y - floor(y);

	
		
	if(x>0){
		
		switch(k){
			case 1:		
				if(yr < ((-m)*xr+p))
					x=floor(x)+1;
			break;

			case 0:
			case 2:
				if(yr < ((m*xr)-p))
					x=floor(x)+1;
			break;
		}
	}

	else if(x<0){
		switch(k){
			case 1:
				if(yr > (m*xr+p))
					x=(int)x-1;
			break;

			case 0:
			case 2:
				if(yr < ((-m)*xr-p))
					x=(int)x-1;
			break;	
		}
	}

	res.x = (int) (0.5*x + 0.5*y);
	res.y = (int) (-0.5*x + 0.5*y); 
	
	return res;
}

