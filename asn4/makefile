OBJS	= assignment4.o
SOURCE	= assignment4.c
HEADER	= 
OUT	= asn
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

assignment4.o: assignment4.c
	$(CC) $(FLAGS) assignment4.c 


clean:
	rm -f $(OBJS) $(OUT)
