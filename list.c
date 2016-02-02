/*      ____________________________________________________                                         
       |_|                == List Code ==                 |_|
       |    You can find here all the source code for the   |
       |               List type we use.		    |
       |                                                    |
       |_                  <=========>                     _|
       |_|________________________________________________|_|
                                                       \   ,__,
                                                        \  (oo)____
                                                           (__)    )\
                                                              ||--|| *  
*/
#include "list.h"

void AppendList(Hexa_list** init, vect val){
	Hexa_list *list=(*init);

	if(*init==NULL){	
		*init = malloc(sizeof(Hexa_list));
		(*init)->next=NULL;
		(*init)->pos=val;			
	}
	
	else{
		while(list->next!=NULL)
			list = list->next;

		list->next = malloc(sizeof(Hexa_list));
		list->next->next=NULL;	
	}
}

void SupprEltList(Hexa_list** init, unsigned int indice){
	Hexa_list *list=(*init), pre=(*init);

	if(list!=NULL){
		if(indice>0){
			while(list->next!=NULL && indice>0){
				pre=list;
				list=list->next;
				indice --;
			}
			if(pre==list)
				list=NULL;

			pre->next=list->next;
			free(list);
		}
		
		else{
			list=list->next;	
		}
	}

}
