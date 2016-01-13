/*

*/
#include "logic.h"


move ValidMove(vect start, vect end, hexa** board, int boardSize){
	vect dpl;
	move Res;
	int normSquare;

	dpl.x=end.x-start.x;
	dpl.y=end.y-start.y;

	if(end.x>=0 && end.x<boardSize && end.y>=0 && end.y<boardSize && board[end.x][end.y].val==EMPTY){
		normSquare=(dpl.x*dpl.x)+(dpl.y*dpl.y);

		if(dpl.x*dpl.y>=0){
			if(normSquare>=4 && normSquare<8)
				Res=JUMP;
			else if(normSquare<=2)
				Res=DUPLICATE;
			else
				Res=INVALIDE;
		}

		else{
			if(normSquare==4)
				Res=JUMP;
			else
				Res=INVALIDE;
		}
	}
	else
		Res=INVALIDE;

	return Res;
}

void main(){	
}
