CC =gcc
CFLAGS =-Wall -O2
RM =/bin/rm -rf

SYSLIBS = -L/usr/X11R6/lib -lXm -lXt -lX11
INCLUDEDIR = -I/usr/X11R6/include

SRCS = lbar.c list.c
OBJS = lbar.o list.o

.c.o:
	$(RM) $@
	$(CC) -c $(CFLAGS) $(INCLUDEDIR) $(SRCS)

all: lbar

lbar: $(OBJS)
 
	$(CC) $(CFLAGS) -o lbar $(OBJS) $(SYSLIBS)

clean: 
	@$(RM) core $(OBJS) lbar

