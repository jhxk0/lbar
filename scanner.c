#include "scanner.h"
static char *path[2*MAXB];
static int bcount;
lbar_item *h, *t;

char *get_path(char *line){
	char x;
	int i=0;
	char temp[100];
	for(i=0;i<strlen(line);i++){
		x = line[i];
	if(x=='\n'){
	    //printf("i found one at %d\n", i);
	  line[i] = '\0';
	}
	}
	//printf("%s\n", line);
	return line;
}

int getrfile(){
	FILE *fp;
	int i, j;
	char *ch, *ch2;
	if((fp = fopen(RFILE, "r")) == NULL){
		perror("fopen");
		return -1;
	}
	lbar_item *c;
	init_list();
	i=0;
	j=1;	
	while(!feof(fp)){
		//ch = getc(fp);
		//if(ch !='\n'){
		//	temp[i] = ch;
		//	i++;
		//}
		//else if(ch =='\n' && j <=MAXB*2){
		
		//temp
			//temp[i] = '\0';
			path[j] = (char *)malloc(100);
			fgets(path[j], 100, fp);
			ch = get_path(path[j]);	
			path[j+1] = (char *)malloc(100);
			fgets(path[j+1], 100, fp);
			ch2 = get_path(path[j+1]);	
			//strcpy(path[j], temp);
			c=new_item();
			c->icon_path=ch;//path[j];
			c->app_path=ch2;//path[j+1];
			add_list(c, j);
			//printf("%s\n", path[j]);
			//i = 0;
			j++;
			bcount++;
		//}
	}
	//print_list(h);
	fclose(fp);
	return 0;
}
