OBJS= bellman.cc
OPTS = -Wall -std=g++

CC=g++

bellman : $(OBJS)
	$(CC) $(OBJS) -o bellman


clean:
	rm -f $(OBJ)

run:    make && ./bellman
