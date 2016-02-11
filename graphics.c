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
extern SDL_Rect hexaBlack;
extern SDL_Rect Token[2];
extern SDL_Rect winText[3];
extern SDL_Rect closed;

void BlitWinner(SDL_Surface *sprite, SDL_Surface *screen, int *score){
	SDL_Rect pos;


	if(score[0]>score[1]){
		pos.x=400-(winText[0].w/2);
		pos.y=300-(winText[0].h/2);
		SDL_BlitSurface(sprite, &winText[0], screen, &pos);
	}


	else if(score[0]==score[1]){
		pos.x=400-(winText[2].w/2);
		pos.y=300-(winText[2].h/2);
		SDL_BlitSurface(sprite, &winText[2], screen, &pos);
	}

	else{
		pos.x=400-(winText[1].w/2);
		pos.y=300-(winText[1].h/2);
		SDL_BlitSurface(sprite, &winText[1], screen, &pos);
	}
}

vect GetOrigineHex(int size){
	vect pos;

	pos.x = 0.5*(800-hexaBlue.w);
	pos.y = 0.5*(600-(size)*hexaBlue.h);
	
	return pos;
}

void BlitGameboard(T_board board, SDL_Surface* screen, SDL_Surface* sprite){
	SDL_Rect Pos, tokenPos;
	vect initPos = GetOrigineHex(board.size);
	
	int i, j;

	initPos.x = 0.5*(800-hexaBlue.w);
	initPos.y = 0.5*(600- (board.size)*hexaBlue.h);

	for(i=0;i<board.size;i++){
		for(j=0;j<board.size;j++){
			Pos.x = (4.0/6.0)*hexaBlue.w*(i-j) + initPos.x;
			Pos.y = 0.5*hexaBlue.h*(i+j) + initPos.y;
			SDL_BlitSurface(sprite, &hexaBlue, screen, &Pos);
			switch(board.grid[i][j].val){
				case PLAYER_1:
					tokenPos = (SDL_Rect){Pos.x+16,Pos.y+10,0,0};
					SDL_BlitSurface(sprite, Token, screen, &tokenPos);
				break;
				
				case PLAYER_2:
					tokenPos = (SDL_Rect){Pos.x+11,Pos.y+7,0,0};
					SDL_BlitSurface(sprite, Token+1, screen, &tokenPos);
				break;
				
				case CLOSED:
					tokenPos = (SDL_Rect){Pos.x+18, Pos.y+15};
					SDL_BlitSurface(sprite, &closed, screen, &tokenPos);
				break;
				default :
				break;
			}
		}
	}
}
void EraseBoard(int size, SDL_Surface* screen, SDL_Surface* sprite){
	SDL_Rect Pos;
	vect initPos = GetOrigineHex(size);
	
	int i, j;

	initPos.x = 0.5*(800-hexaBlue.w);
	initPos.y = 0.5*(600- size*hexaBlue.h);

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			Pos.x = (4.0/6.0)*hexaBlack.w*(i-j) + initPos.x;
			Pos.y = 0.5*hexaBlack.h*(i+j) + initPos.y;
			SDL_BlitSurface(sprite, &hexaBlack, screen, &Pos);
		}
	}
}
vect GetHexaCoor(T_board board, vect cursor){
	vect initPos = GetOrigineHex(board.size), res;	
	
	double posX, posY, posReCentX, posReCentY, coefCurv, p;
	
	int k=0;

	initPos.x=initPos.x+(hexaBlue.w/2);
	initPos.y=initPos.y;
	
	posX = (cursor.x-initPos.x) / ((4.0/6.0)*hexaBlue.w);
	posY = (cursor.y-initPos.y) / (0.5*hexaBlue.h);
	

	k= (int)posX%2 + (int)posY%2;
	coefCurv = 4.0/2.0;
	p = 2.0/3.0;

	posReCentX = posX - (int)posX;
	posReCentY = posY - (int)posY;	
		
	if(posX>0){
		
		switch(k){
			case 1:		
				if(posReCentY < ((-coefCurv)*posReCentX+p))
					posX=(int)posX+1;
			break;

			case 0:
			case 2:
				if(posReCentY < ((coefCurv*posReCentX)-p))
					posX=(int)posX+1;
			break;
		}
	}

	else if(posX<0){
		switch(k){
			case 1:
				if(posReCentY > (coefCurv*posReCentX+p))
					posX=(int)posX-1;
			break;

			case 0:
			case 2:
				if(posReCentY < ((-coefCurv)*posReCentX-p))
					posX=(int)posX-1;
			break;	
		}
	}

	res.x = (int) (0.5*posX + 0.5*posY);
	res.y = (int) (-0.5*posX + 0.5*posY); 

	return res;
}

