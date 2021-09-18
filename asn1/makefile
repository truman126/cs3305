OBJS	= assignment1.o
SOURCE	= assignment1.c
HEADER	= 
OUT	= asn
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

assignment1.o: assignment1.c
	$(CC) $(FLAGS) assignment1.c 


clean:
	rm -f $(OBJS) $(OUT)
