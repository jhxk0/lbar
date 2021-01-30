#include <stdio.h>
#include <Xm/XmAll.h>

struct linked_list {
	struct linked_list *next;
	struct linked_list *prev;
	char   *app_path;
	char   *icon_path;
	Widget button;
	Pixmap pix;
	int id;
};

typedef struct linked_list lbar_item;

lbar_item* new_item();
void init_list();
void init_lbar_item(lbar_item *);
void add_list(lbar_item *, int);
void print_list(lbar_item *);

