/*      ____________________________________________________
       |_|              == List Header ==                 |_|
       |  You can find here all data struture and function  |
       |            prototype for the List type 	    | 
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
						       \   ,__,
						        \  (oo)____
           						   (__)    )\
              					              ||--|| *
*/

#ifndef LIST
#define LIST

#include "logic.h"
#include <stdlib.h>


typedef struct list{
	vect pos;	
	struct list* next;	
}Hexa_list;

void AppendList(Hexa_list** init, vect val);
void SupprEltList(Hexa_list** init, unsigned int indice);
#endif
