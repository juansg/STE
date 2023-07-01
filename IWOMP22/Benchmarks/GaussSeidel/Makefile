CC	= clang-12
LD	= $(CC)

CFLAGS	= -g -Wall 
CFLAGS	+= -I. 
LDFLAGS	= 

OBJS	= 
LIBS    = -lm -fopenmp=libiomp5 -mrtm

SRCS	= $(patsubst %.o,%.c,$(OBJS))

PRGS	= gs_seq  gs_task  gs_STE 
#gs_taskloop gs_openmp

all: $(PRGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c $(INCLUDE) -o $@ -fopenmp=libiomp5 -mrtm

$(PRGS): $(OBJS)
$(PRGS): 
$(PRGS): % : %.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	-rm -f *.o  *~ $(PRGS)

