OBJS	= assignment5.o
SOURCE	= assignment5.c
HEADER	= 
OUT	= asn
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

assignment5.o: assignment5.c
	$(CC) $(FLAGS) assignment5.c 


clean:
	rm -f $(OBJS) $(OUT)
