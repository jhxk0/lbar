#include "list.h"

extern lbar_item *h, *t;

void init_lbar_item(lbar_item *l){
	l->next = NULL;
	l->prev = NULL;
	l->app_path = NULL;
	//l->pix = NULL;
	l->button = NULL;
	l->id = 0;
}

lbar_item* new_item(){
	lbar_item *b;
	b=(lbar_item*)malloc(sizeof(lbar_item));

	if(b==NULL) return NULL;
	init_lbar_item(b);
	return b;
}

void init_list(){
	h=new_item();
	h->id = 0;
	t=new_item();
	//t1=new_item();
	t->id = 1;
	//t1=t;
	//t1->button=1;
	h->next = t;
	t->prev = h;
	t->next=NULL;
}
void add_list(lbar_item *d, int j){
	t->next = d;
	d->prev = t;
	d->id = j+1;
	//d->next = t;
	t = d;
}
void print_list(lbar_item *e){
	while(e->next!= NULL){
		if(e->prev!= NULL)
		printf("%s\n%s\n%d %d\n", e->app_path, e->icon_path, e->id, e->prev->id);
		e = e->next;
	}
}
		
		
