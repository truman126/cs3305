OBJS	= assignment3.o
SOURCE	= assignment3.c
HEADER	= 
OUT	= asn
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

assignment3.o: assignment3.c
	$(CC) $(FLAGS) assignment3.c 


clean:
	rm -f $(OBJS) $(OUT)
