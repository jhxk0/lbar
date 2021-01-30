/* launch bar */
#include "lbar.h"
#include "list.h"

//XtActionProc showtooltip(Widget w, XEvent *event, String *args, int *num_args);
//XtActionProc destroy(Widget parent, XEvent *event, String *args, int *num_args);

static String fallbacks[] = {
	"lbar*fontlist: -adobe-courier-bold-r-normal--20-*=TAG1",
	"lbar*fontlist: -adobe-courier-bold-r-normal--12-*=TAG2",
	NULL
};

/*static String translations = "<Btn1Down>:	showtooltip()\n\
<Btn1Up>:	destroy()";*/

//static XtActionsRec transactions[] = {
//	{"showtooltip", (XtActionProc)showtooltip},
//	{"destroy", (XtActionProc)destroy}
//};

XtAppContext app;
Widget top, form, tlabel, cframe;
Widget pop, sep;
lbar_item *h, *t;
XmString ts;
Pixel fg, bg;
XtTranslations no_drag;

void DoNothing() {}

static char noDragTranslations[] = "#override <Btn2Down>: DoNothing()";
static XtActionsRec noDragActions[] =
        {{"DoNothing", (XtActionProc) DoNothing}};


static char *path, *path2;
//static int bcount;

char *get_path(char *line){
	char x;
	int i = 0;
	for(i=0;i<strlen(line);i++){
		x = line[i];
	if(x=='\n')
	  line[i] = '\0';
	}
	return line;
}

int getrfile(){
	FILE *fp;
	int j;
	char *ch, *ch2;
	if((fp = fopen(RFILE, "r")) == NULL){
		perror("fopen");
		return -1;
	}
	lbar_item *c;
	init_list();
	j=1;	
	while(!feof(fp)){
			path = (char *)malloc(50);
			fgets(path, 50, fp);
			ch = get_path(path);	
			path2 = (char *)malloc(50);
			fgets(path2, 50, fp);
			ch2 = get_path(path2);	
			//strcpy(path[j], temp);
			c = new_item();
			c->icon_path = ch;
			c->app_path = ch2;
			add_list(c, j);
			j++;
			//bcount++;
	}
	free(path); free(path2);
	//print_list(h);
	fclose(fp);
	return 0;
}

void seticons(lbar_item *ex){
	XtVaGetValues(ex->button, XmNforeground, 
			&fg, XmNbackground, &bg, NULL);	
	ex->pix = XmGetPixmap(XtScreen(ex->button), ex->icon_path, fg, bg);
	//if (ex->pix == NULL)
	//ex->pix = XmGetPixmap(XtScreen(ex->button), 
//			"/home/kalyon/lbaricons/unknown.xpm", fg, bg);
	XtVaSetValues(ex->button, XmNlabelType, XmPIXMAP, 
			XmNlabelPixmap, ex->pix, NULL, 0);
}

void butCB(Widget w, XtPointer cd, XtPointer cb){
	char *run = (char *) cd;
	pid_t pid;
		switch(pid = fork()){
		case -1: 
			perror("fork");
			return;
			break;
		case 0: 
			system(run);
			_exit(0);
			break;
		default:
			waitpid(pid, NULL, 0);
			break;
		}
}

void lbutCB(Widget w, XtPointer cd, XtPointer cb){
	pid_t pid;
		switch(pid = fork()){
		case -1: 
			perror("fork");
			return;
			break;
		case 0: 
			system(XLOCKPATH);
			_exit(0);
			break;
		default:
			waitpid(pid, NULL, 0);
			break;
		}
}

void exitCB(Widget w, XtPointer cd, XtPointer cb){
	//int i;
	//for(i=1;i<(MAXB+1);i++)
	//	free(path[i]);
	exit(0);
}

/*XtActionProc destroy(Widget parent, XEvent *event, String *args, int *num_args)
{
	XtDestroyWidget(pop);
}

XtActionProc showtooltip(Widget w, XEvent *event, String *args, int *num_args)
{
	Widget tiplabel;
	XmString ds;
	time_t t;
	struct tm s;
	char temp[256];
	int x=0, y=0;
	int x1=0, y1=0;	
	XColor co;


	XtVaGetValues(top, XmNx, &x, XmNy, &y, NULL);
	XtVaGetValues(cframe, XmNx, &x1, XmNy, &y1, NULL);
	pop = XtVaAppCreateShell("tip", "tool", wmShellWidgetClass,
		XtDisplay(w),
		XmNoverrideRedirect, True,
		XmNsaveUnder, True,
		XmNallowShellResize, False,
		XmNwidth, 150,
		XmNheight, 25,
		NULL);
	if(y <= 30)
		XtVaSetValues(pop, XmNx, x + x1 - 90, XmNy, y + 30, NULL);
	else
		XtVaSetValues(pop, XmNx, x + x1 - 90, XmNy, y - 30, NULL);
	
	time(&t);
	s = *localtime(&t);
	strftime(temp, 256, "%d %b %Y, %A", &s);
	ds = XmStringCreateLtoR(temp, "TAG1");
	co.red = 255<<8;co.green=255<<8;co.blue=255<<8;
	XAllocColor(XtDisplay(w), DefaultColormapOfScreen(XtScreen(w)), &co);
	tiplabel = XtVaCreateManagedWidget("tiplabel", xmLabelWidgetClass,
			pop,
			XmNlabelString, ds, 
			XmNbackground, co.pixel,
			NULL);
	XmStringFree(ds);
	XtPopup(pop, XtGrabNone);
	return 0;
}*/
/*	
void updatetimedate(){
	time_t t;
	struct tm *s;
	long updatetime = 0;
	char temp[100];
	char temp2[100];
	int timeout = 0;
	XmString ts1, ts2;
	XmRenderTable render_table;
	XmRendition rendition;
	int n;
	Arg args[10];

	time(&t);
	s = localtime(&t);
	strftime(temp, 100, "%H:%M:%S\n", s);
	strftime(temp2, 100, "%d %b %Y", s);

	
	n = 0;
	XtSetArg (args[n], XmNfontName, "-adobe-utopia-bold-r-normal-*-*-180-*"); n++;
	XtSetArg (args[n], XmNfontType, XmFONT_IS_FONT); n++;
	XtSetArg (args[n], XmNloadModel, XmLOAD_IMMEDIATE); n++;
	rendition = XmRenditionCreate (top, "tag1", args, n);
	render_table = XmRenderTableAddRenditions (NULL, &rendition, 1,
			                                             XmMERGE_NEW);
	XmRenditionFree (rendition);
	n = 0;
	XtSetArg (args[n], XmNfontName, "-b&h-lucidatypewriter-medium-r-normal-*-*-140-*-*-m-*"); n++;
	XtSetArg (args[n], XmNfontType, XmFONT_IS_FONT); n++;
	XtSetArg (args[n], XmNloadModel, XmLOAD_IMMEDIATE); n++;
	rendition = XmRenditionCreate (top, "tag2", args, n);
	render_table = XmRenderTableAddRenditions (render_table, &rendition,
			                                           1,XmMERGE_NEW);
	XmRenditionFree (rendition);
	
	ts1 = XmStringGenerate(temp, "tag1",
	      XmCHARSET_TEXT, NULL);
	
	ts2 = XmStringGenerate(temp2, "tag2",
			      XmCHARSET_TEXT, NULL);
			
	ts = XmStringConcatAndFree(ts1 , ts2);
	XtVaSetValues(tlabel, XmNlabelString, ts, 
			      //XmNrenderTable, render_table, 
			      NULL);
	
	XmStringFree(ts);
	updatetime = (1 - s->tm_sec % 1) * 1000;
	timeout = XtAppAddTimeOut(app, updatetime, updatetimedate, NULL);
}*/
void set_buttons(lbar_item *ce){
	while(ce->next!=NULL){
	if(ce->id > 1){
	  ce->button = XtVaCreateManagedWidget("but", xmPushButtonWidgetClass,
				form,
				XmNshadowThickness, 0,
				XmNhighlightThickness, 0,
				XmNfillOnArm, False,
				//XmNleftOffset,2,
				//XmNrightOffset,2,
				XmNtopAttachment, XmATTACH_FORM,
				XmNbottomAttachment, XmATTACH_FORM, 
				XmNleftAttachment, XmATTACH_WIDGET,
				XmNleftWidget, ce->prev->button,
				//XmNbackground, co.pixel,
				NULL);
		seticons(ce);
	  XtAddCallback(ce->button, XmNactivateCallback, butCB, 
			  (XtPointer)ce->app_path);
	}		
	ce = ce->next;
	}
	 sep = XtVaCreateManagedWidget("sep", xmSeparatorWidgetClass, form,
			 XmNorientation, XmVERTICAL,
			 XmNtopOffset, 5,
			 XmNbottomOffset, 5,
			 XmNleftOffset, 5,
			 //XmNheight, 32,
			 XmNtopAttachment, XmATTACH_FORM,
			 XmNbottomAttachment, XmATTACH_FORM, 
			 XmNleftAttachment, XmATTACH_WIDGET,
			 XmNleftWidget, ce->prev->button,
			 NULL);
}
int main(int argc, char **argv){
	Widget lbut, exitb;
	Pixmap lpix, epix;
	//int i, maxb = MAXB;
	//XColor co;


	if(getrfile() < 0){
		fprintf(stderr, "cant find config file\n");
		exit(-1);
	}
	top = XtVaOpenApplication(&app, "lbar", NULL, 0, &argc, argv, NULL,
			sessionShellWidgetClass, 0);
	//if(XmIsMotifWMRunning(top))
	XtVaSetValues(top, XmNmwmDecorations, 0, 
			XmNmwmFunctions, 0, 
			NULL);
	no_drag = XtParseTranslationTable(noDragTranslations);
	XtAppAddActions(app, noDragActions, XtNumber(noDragActions));

	form = XtVaCreateManagedWidget("form", xmFormWidgetClass, top,
			//xmRowColumnWidgetClass, top,
			//XmNorientation, XmHORIZONTAL,
			XmNhorizontalSpacing, 1,
                        XmNverticalSpacing, 2,
			//XmNshadowThickness, 3,
			//XmNhighlightThickness, 3,
			NULL);

	/*co.red = 172<<8;co.green=178<<8;co.blue=197<<8;
	XAllocColor(XtDisplay(top), DefaultColormapOfScreen(XtScreen(top)), &co);*/
	//print_list(h);
	set_buttons(h);	
	 lbut = XtVaCreateManagedWidget("lbut", xmPushButtonWidgetClass,
				form,
				XmNshadowThickness, 0,
				XmNhighlightThickness, 0,
				XmNfillOnArm, False,
				//XmNtopOffset,2,
				XmNtopAttachment, XmATTACH_FORM,
				XmNleftAttachment, XmATTACH_WIDGET,
				XmNleftWidget, sep,
				XmNrightAttachment, XmATTACH_FORM,
				//XmNbackground, co.pixel,
				NULL);	  
	XtVaGetValues(lbut, XmNforeground, &fg, XmNbackground, &bg, NULL);
	lpix = XmGetPixmap(XtScreen(lbut), LOCKIPATH, fg, bg);
	XtVaSetValues(lbut, XmNlabelType, XmPIXMAP, 
			XmNlabelPixmap, lpix, NULL, 0);
	 XtAddCallback(lbut, XmNactivateCallback, lbutCB, NULL);
	 
	 exitb = XtVaCreateManagedWidget("exitb", xmPushButtonWidgetClass,
				form,
				XmNshadowThickness, 0,
				XmNhighlightThickness, 0,
				//XmNbottomOffset,2,
				XmNfillOnArm, False,
				XmNtopAttachment, XmATTACH_WIDGET,
				XmNtopWidget, lbut,
				XmNbottomAttachment, XmATTACH_FORM, 
				XmNrightAttachment, XmATTACH_FORM, 
				XmNleftAttachment, XmATTACH_WIDGET,
				XmNleftWidget, sep,
				//XmNbackground, co.pixel,
				NULL);	  
	XtVaGetValues(exitb, XmNforeground, &fg, XmNbackground, &bg, NULL);
	epix= XmGetPixmap(XtScreen(exitb), EXITIPATH, fg, bg);
	XtVaSetValues(exitb, XmNlabelType, XmPIXMAP, 
			XmNlabelPixmap, epix, NULL, 0);
	XtAddCallback(exitb, XmNactivateCallback, exitCB, NULL);

	//XtOverrideTranslations(tlabel, XtParseTranslationTable(translations));
	//XtAppAddActions(app, transactions, XtNumber(transactions));
	XtRealizeWidget(top);
//	updatetimedate();	
	XtAppMainLoop(app);
	return 0;
}
